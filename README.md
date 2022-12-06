# Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
An interactive Qt application to visualize [OTF2](https://www.vi-hps.org/projects/score-p/) trace files.

## Dependencies

- C++20 compatible compiler
- [CMake](https://cmake.org)
- [Qt5/6 (incl. Qt Widgets)](https://www.qt.io)
- [otf2](http://www.vi-hps.org/projects/score-p/)
- [otf2xx](https://github.com/tud-zih-energy/otf2xx)

## Build

1. Clone this repository: `git clone https://github.com/b-gehrke/motiv`
2. Change to cloned repository: `cd motiv`
3. Initialise the submodules: `git submodule update --init --recursive`
4. Generate build system with CMake: `cmake -S . -B build`
5. Build the project: `cmake --build build`

## License
MOTIV is licensed under GPL v3 or later. The license is available [here](COPYING).