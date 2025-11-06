
# seraph

*A lightweight 2-D game framework written over SFML 3*

This project is a work-in-progress. It was originally a library for SFML 2,
but has recently been updated for SFML 3.

The project is currently working towards being header-only for the following
reasons:

(1) *Negligible compilation time*: The main library takes only seconds
    to compile, and any larger sections are currently remaining as a separate
    header and source.
(2) *C++ modules*: Modules are on the horizon for practical use with modern
    compilers! This will prefer code oriented in this direction.
(3) *The more code a compiler can see at once, the better the optimizations*
