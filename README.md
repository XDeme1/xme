# XME Library
This is a hobby project, made to provide some utilies in c++
## Requirements
Minimum is c++20.

The following minimum versions are required:

* GCC 12.3
* Clang 11
* Visual Studio Not tested.

## Usage with cmake
```cmake
target_compile_features(<target> PRIVATE cxx_std_20) # C++20 is required
target_link_libraries(<target> PRIVATE xme)
```

## Components
* ### Math
    Lives under the `xme::math` namespace. To use it, include `<xme/math/math.hpp>` or other parts separately.

    For detailed information see the [math directory](./include/xme/math).

## C++20 Modules
Currently modules only works with libc++ and clang 18+.
This library will shift to being modules only, when stabilizes in clang and gcc. 

To enable modules in cmake define the following before including
```cmake
set(XME_BUILD_MODULES ON)
```
