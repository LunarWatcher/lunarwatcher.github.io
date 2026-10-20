---
{
    "title": "Running the same test on multiple data in catch2",
    "date": "2026-10-21T00:40:35+02:00",
    "type": "blog",
    "taxonomies": { "tags": [ "cpp", "catch2" ] }
}
---

For the record, using a `TEST_CASE_METHOD` is fairly simple; it's the same as a regular `TEST_CASE`, but with an extra prefixed argument corresponding to a class:
```cpp
struct Fixture;
TEST_CASE_METHOD(Fixture, "Name", "[tags]") { /* ... */ }
```

Each test run acts as if it's an instance of the `Fixture`, so any functions in the class can be called. This is basically just the same as
```cpp
TEST_CASE("Name", "[tags]") {
    Fixture f;
}
```

but with some syntactic sugar and not needing to call `f.` to access the methods in the fixture.

I have not fully landed on where I stand on proper catch2 fixtures vs. pseudo-fixtures (standalone data objects, see the TEST_CASE example above). But a few months ago, I did have a use for this with [magpie](https://codeberg.org/LunarWatcher/magpie). At the time of the test being written, I had just written an HTTP/1.1 parser, and wanted to run the entire existing test suite on both HTTP/1.1 and HTTP/2.

Because this is a protocol test rather than an internals test, both the test cases are expected to behave the same. Some of the data validation that checks things specific to HTTP/2 does vary, but this isn't super important.

The tests in question actually use both Catch2 fixtures and pseudo-fixtures, and use the catch2 fixture to initialize a pseudo-fixture, since that's where all of the shared server state lies. I suspect I'll try refactoring this at some point.

Anyway, I'm not going to rewrite all of my tests in any major way, but `TEST_CASE_METHOD` with a Catch2 fixture allows for template use to generate, in my case, two variants of the same test. Both paths lead to calling the same test function, but one calls setup for HTTP/1.1, and the other for HTTP/2. 

Slap it in a macro, and it's fairly easy to create custom `TEST_CASE` types:

```cpp
struct HttpEngineTestContext { /* Context data omitted */ };

struct EngineTestFixture {
    virtual ~EngineTestFixture() = default;

    void withHttp11() {
        HttpEngineTestContext ctx { /* Omitted */ };
        testCase(&ctx);
    }
    void withHttp2() {
        HttpEngineTestContext ctx { /* Omitted */ };
        testCase(&ctx);
    }

    virtual void testCase(
        EngineTestContext* context
    ) = 0;
};

#define INTERNAL_HTTP_ENGINE_TEST_CASE(TestIdentifier, Name, ...)       \
    struct TestIdentifier : public test::EngineTestFixture {            \
        virtual void testCase(test::EngineTestContext* context) override; \
    };                                                                  \
    TEST_CASE_METHOD(TestIdentifier, "HTTP/1.1: " Name, "[http11]" __VA_ARGS__) { \
        withHttp11();                                                   \
    }                                                                   \
    TEST_CASE_METHOD(TestIdentifier, "HTTP/2: " Name, "[http2]" __VA_ARGS__) { \
        withHttp2();                                                    \
    }                                                                   \
    void TestIdentifier::testCase(test::EngineTestContext* context)

#define HTTP_ENGINE_TEST_CASE(Name, ...)                \
    INTERNAL_HTTP_ENGINE_TEST_CASE(                     \
        INTERNAL_CATCH_UNIQUE_NAME(MAGPIE_TEST_IMPL),   \
        Name,                                           \
        __VA_ARGS__                                     \
    )
```

In retrospect, I probably could've merged the TestContext into the fixture, but I wanted to make the same setup reusable if I ever end up adding non-HTTP protocols to [magpie](https://codeberg.org/LunarWatcher/magpie). That's just a design detail that isn't super important for the actual test.

Here's an actual test (minus some of the validation for brevity) that uses the new test case type:
```cpp
HTTP_ENGINE_TEST_CASE("Test compression") {
    // Editor's note: in this case, because we pass in a context rather than use the fixture as the context,
    // it's given as an argument rather than something dereferencable by `this->`. This was purely a subjective
    // design decision that made sense at the time and in context.
    TestApp app(context);

    app->route<"/", magpie::Method::Get>([](auto*, auto& req, magpie::Response& res) {
        res = magpie::CompressedResponse(
            req,
            magpie::Status::OK,
            "Rawr x3 nuzzles pounces on you"
        );
    });
    app.start();
    cpr::Response res;

    // Actual test code inside these has been omitted, but it's just three `Get` requests
    SECTION("Requesting the identity compression should not result in compression") {}
    SECTION("Requesting gzip should result in gzip") {}
    SECTION("Requesting deflate should result in deflate") {}

    REQUIRE(res.text == "Rawr x3 nuzzles pounces on you");
}
```

Because of the macro expansion, this results in two tests that point to the same fixture, where the fixture has an attached TestCase function. This test case function is the body shown in the test. They also differ in name to make it easy to tell which version of the test failed, if for example only one of the two protocols fail.

This implementation is largely based on how the actual `TEST_CASE` macro is implemented, since it also pre-declares a function, and then doesn't terminate it so the subsequent function body is actually secretly a function declaration in a trenchcoat.

---

As an aside, I'm still experimenting with how to best use Catch2 test fixtures. I do recommend them though. I may have made some design mistakes here, but they're still really useful for reducing repeated code in tests, and I desperately need to get better at writing fixtures. It's hard to know what's reusable though.

An unrelated case I had is in [violet](https://lunarwatcher.codeberg.page/violet), where I have some E2E tests that test all the way from a command line invocation. The fixture has some state to care about, and some configurable bits before the actual generation happens. 

This could be a single fixture with a constructor (or a few constructors), but it subjectively _feels_ better to just
```cpp
TEST_CASE_METHOD(tests::E2EFixture, "When a prefix is set and --prefix", "[e2e]") {
    conf.prefix = "/prefix";
    loadSite();

    SECTION("is not passed on the command line") {
        run({
            "generate", "-d"
        });
        requireOutput(); // Fixture function; runs some standard assertions
        // Validation omitted
    }
}
```

I still have a fair bit to learn on writing decent supporting code for test code though. I'll probably end up refactoring at least the markdown tests at some point. one of the current issues there is that I have a lot of tests that hardcode HTML, which would be an easy fixture setup to avoid having to fix a bunch of tests just because I change an ID somewhere.
