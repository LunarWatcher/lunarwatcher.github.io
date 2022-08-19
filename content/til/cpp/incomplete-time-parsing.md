---
title: "C++ time sucks: incomplete time parsing"
tags: ["c++"]
date: 2022-08-19T19:50:19+02:00
---

C++ time parsing is trash. HowardHinnant/date is equally bad, but it also adds timezone parsing. C++20's time additions is just HowardHinnant/date without the name.

Using the old `std::get_time`, because the vast majority of distros and compilers haven't implemented the new garbage (HowardHinnant/date), and it doesn't fix the core problem anyway.

Say you have a date similar to what journald logs contain: `Aug 17 22:17:44`. Guess what happens if you try parsing it.

That's right, the time representation, as well as the year is completely fucked, because it doesn't include the year. Fortunately, this is possible to work around with `std::get_time`. HowardHinnant/date does not seem to offer this, making it still trash and definitely worth avoiding at all cost.

The `tm` struct passed around to various methods:tm: isn't cleared, _and_ it uses the contextual data you've provided to yield a usable date. This means that shoving in `2022 - 1900` actually provides a correct date for the journald strings. Unfortunately, it seems to still misbehave, so I took it one step further:

```cpp
// Get the current time
std::time_t currTimeMillis = std::time(nullptr);
// note that this is an std::tm*
// You may want to use std::gmtime if you're parsing UTC dates instead of
// localtime dates. Not really sure how this works. Just worked when I tried filling
// in the fields, and that's good enough for me.
auto tm = std::localtime(&currTimeMillis);

// parse the time as usual
std::stringstream ss(timeString);
ss >> std::get_time(tm, timePattern.c_str());

// And then convert it back to a chrono timestamp
auto res = std::chrono::system_clock::from_time_t(std::mktime(tm));
```

The idea here is to let the parser override the time in all undefined fields. This means that everything else is compared relative to today. Did only the day, month, and time get inputted? Use the current year, infer the millis from that. Stonks!

Though honestly, std::chrono having such abysmal support presents challenges. To print it, it has to be converted back to a `struct tm`, and shoved through `put_time`, or alternatively `strftime` if you happen to understand the parameters of it.
It might be worth just leaving it as an `std::tm` instead to avoid unnecessary conversions.

Note that there may be manual cleanup of the `strct tm*`. The man page for `std::localtime` wasn't clear on that.
