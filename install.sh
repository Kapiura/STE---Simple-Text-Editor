#!/bin/bash
mkdir build;
git clone https://gitlab.com/aminosbh/sdl2-cmake-modules.git cmake/sdl2
rm -rf cmake/sdl2/.git
cd build;
cmake ..;
make;
./ste;
