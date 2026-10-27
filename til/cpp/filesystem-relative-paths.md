---
{
    "title": "Relative input path to std::filesystem::relative is incorrectly parsed as relative to the current working directory",
    "date": "2026-10-27T21:04:28+01:00",
    "type": "til",
    "taxonomies": {
        "tags": ["cpp", "std-filesystem"]
    }
}
---

To be clear, I mean that this is weird behaviour with the two-arg signature of `std::filesystem::relative`, and when the first argument is relative. The 1-arg version is the same as the two-arg version, but where the base is set to the current working directory, which obviously is going to make relative paths; that's not the problem I'm talking about here.

I just had to handle a strange bug involving `std::filesystem::relative` in [violet](https://codeberg.org/LunarWatcher/violet). It did not affect my use in production, but it did affect tests that tried to debug an unrelated bug. The function was meant to return a list of path segments, so given `some/file/path.md`, `some` and `file` should be pushed to a segment list. The source bug was that they were pushed in the wrong order, but when writing tests, the segment list was empty.

Some tests that used this function did not fail due to being incorrectly configured, and they provided a full path. Violet at runtime does not, and provides relative paths. If `std::filesystem::relative` gets a relative path as its first argument, it's for whatever reason interpreted as being relative to the current working directory, and returns an empty string if the file doesn't exist:

```cpp
#include <iostream>
#include <filesystem>
#include <string>

int main()
{
    std::filesystem::path root = "/tmp/folder";
    std::filesystem::path rel = "sub/file.md";

    std::filesystem::create_directories("/tmp/folder/sub");

    std::cout << "cwd at start: " << std::filesystem::current_path() << std::endl;
    // prints 1
    std::cout << std::filesystem::exists(root) << std::endl;
    // prints "" <--- wtf
    std::cout << std::filesystem::relative(rel.parent_path(), root).string() << std::endl;

    std::filesystem::current_path("/tmp/folder");
    // prints "sub"
    std::cout << std::filesystem::relative(rel.parent_path(), root).string() << std::endl;
}
```

I don't understand why this happens; it's not that it cares about non-existent files, because you can get a non-existent working directory out of, for example,
```cpp
// Empty
std::cout << std::filesystem::relative(std::filesystem::path("non-existent/file.md").parent_path(), root).string() << std::endl;
// prints non-existent (as expected)
std::cout << std::filesystem::relative(std::filesystem::path(root / "non-existent/file.md").parent_path(), root).string() << std::endl;
```

cppreference suggests that [`std::filesystem::proximate` would be more appropriate](https://en.cppreference.com/cpp/filesystem/relative), which also seems to work:
```cpp
// prints non-existent
std::cout << std::filesystem::proximate(std::filesystem::path("non-existent/file.md").parent_path(), root).string() << std::endl;
// prints non-existent
std::cout << std::filesystem::proximate(std::filesystem::path(root / "non-existent/file.md").parent_path(), root).string() << std::endl;
```

`proximate` is a dogshit name, especially since it's only understandable by [reading the standard proposing the function](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0219r0.html#Provide-separate-proximate). All it does is return the first argument if `relative` would've failed (i.e. returned an empty string when it shouldn't[^1] have), basically.

TL;DR: use `std::filesystem::proximate`, or provide absolute paths. Or, as I ended up doing, just use the relative path directly. `std::filesystem::relative` on a relative path is unnecessary. `std::filesystem::proximate` should still be a useful substitute if the input paths may or may not be relative though.

[^1]: I use "shouldn't" in this case to refer to a logical shouldn't rather than a standard shouldn't. I assume this is the intended behaviour, but the intended behaviour is incredibly backwards here.
