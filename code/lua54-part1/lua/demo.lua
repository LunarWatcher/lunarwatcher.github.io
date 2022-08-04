local demo = require 'demo';
demo.cerr();

-- This should error
-- demo.cerrarg();
demo.cerrarg("[error] Hello from Lua");
-- demo.cerrarg(1234)

warn("@on")
warn(54);

-- Test cases for cerrargs
demo.cerrargs("a", 42);
demo.cerrargs("a", "42");
demo.cerrargs("b");
-- This should also error
--demo.cerrargs()
demo.cerrargs(false, true, false, 420, "a", nil, nil, nil)

print("Hello, World!");

print(demo.mathmagic(0));
print(demo.mathmagic(10));
print(demo.mathmagic(0.4));
