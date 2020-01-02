# LED DOT MATRIX
Small C++ library for driving a LED Dot Matrix with MAX7219 chip through SPI.

This library provides some abstractions around the linux spidev, in order to drive a dot matrix through a (series of) MAX7219 IC(s).  
Check out `test/main.cpp` to see how to use the library.

## Building

1. Install premake5
2. Configure build with `premake5 gmake2`
3. Build library with `make`
4. Run test-script `./bin/LDMTest`
