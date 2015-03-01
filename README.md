# cpp-variant-type
Simple, easy to use and non-effective template variant type.

# Simple usage -> allow compiler to detect type implicitly
```C++
Variant intVariant = 5;
Variant boolVariant( true );
Variant stringVariant = std::string("Hello String");

std::cout << "intVariant value: " << intVariant.value<int>() << std::endl;
std::cout << "boolVariant value: " << boolVariant.value<bool>() << std::endl;
std::cout << "stringVariant value: " << stringVariant.value<std::string>() << std::endl;

try {
    char* badCast = stringVariant.value<char*>(); // producing std::bad_cast exception
}
catch ( std::bad_cast& ) {
    std::cout << "Cannot cast std::string to char*" << std::endl;
}
```

# Force setting type
```C++
Variant var;
var.setValue<long>(5);

std::cout << "var<long> value: " << var.value<long>() << std::endl;
```

# Resetting variant type
```C++
 var.setValue<int>(5);
std::cout << "var<int> value: " << var.value<int>() << std::endl;
```

# Testing for equality
```C++
Variant v0 = 5;
Variant v1 = 5;
std::cout << "v0 is equal to v1: " << (v0 == v1) << std::endl;

Variant v2 = 5l;
std::cout << "v0 is equal v2: " << (v0 == v2); // returns false, because types are different ( int and long )
```
