<img alt="LED DOT MATRIX" src="./logo.svg" width="100%">

C++ library for driving a LED Dot Matrix with MAX7219 ICs through SPI.

This library provides some abstractions around the linux spidev, in order to drive a dot matrix through a (series of) MAX7219 IC(s).
Check out `test/main.cpp` for a quick primer on how to use the library.


## Building library
Follow these steps to build this library (and test code).
  1. Install [premake5](https://premake.github.io/download.html)
  2. Enable SPI (necessary on RPi)
  2. Configure build with `premake5 gmake2`
  3. Build library with `make`
  4. Run test-script `./bin/LDMTest`


## Using this library
You can follow the steps above to generate a library file, which you can then use in any project.  
Another way of using this library, is to clone this repository in a subfolder of your project (eg. git submodule), and include it in your own premake file:

```lua
workspace "YourWorkspace"
-- Workspace related configurations

include "path/to/ldm-library/ldm.lua"

project "YourProject"
-- Create your project here

  includedirs {
    "path/to/ldm-library/include",
  }

  links {
    "LedDotMatrix",
  }
```

Check out the `premake5.lua` of this repo for an example.


## Assumptions
This library was build around the 4-in-1 MAX7219 led dot matrices, and as such is built with a few assumptions in mind:
  * The different 8x8 matrices are layed out in a single row.
  * The MAX7219 are cascaded such that the rows of each 8x8 matrix get programmed at the same time (through SPI cascading).
  * The last matrix in the cascade contains the point of origin (0, 0) in the top-left corner.

If your use-case does not conform with these assumptions, you will have to modify this library or look elsewhere for a different library.
The 2 last assumptions can be quite easily fixed by modifying the `flush()` method in _src/matrix.cpp_.
