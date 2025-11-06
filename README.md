
# seraph

*A lightweight 2-D game framework written over SFML 3*

## About

This project is a work-in-progress. It was originally written for SFML 2, but
has recently been updated to SFML 3.

I'm currently working towards it being header-only because:

1. The main library takes only seconds to compile already, and any larger
   sections are really only that way as an old formality.
2. C++ modules are on the horizon for practical use with modern compilers
   (i.e., MSVC, GNU, and Clang)! This will prefer code oriented in this
   format.
3. As always, the more code a compiler can see at once, the better the
   optimizations.

# Building

Compiles easily in VSCode with Microsoft's official CMake plugin. Otherwise,
try the following command from the project directory:

```
cmake --build ./build --config Debug --target all --
```
