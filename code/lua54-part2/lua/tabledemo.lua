local lib = require "tables"

print()
print("table creation")
print(lib.get())
print(lib.get()["key"]);
print(lib.get()[78.9]);


print()
print("List creation");
print(type({1, 2, 3}))
local arr = lib.arrget();
print(arr);
print(arr[1])
print(arr[2])

print()
print("Table reading")
print(lib.read({
    insert = "ploop",
    explode = "boom",
    pirate = "Enceladus corp would like to know your location"
}))
print(lib.read({
    insert = "ploop",
    explode = "boom",
}))
print(lib.read({
    insert = "I use arch btw",
    explode = "boom",
}))

print()
print("Array reading")
print(lib.arrread({1, 4, 3, 4}))
--print(lib.arrread({7}))

print()
print("Module globals")
lib.theAnswer = 6
print(lib.theAnswer);
