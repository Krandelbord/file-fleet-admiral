# File Fleet Admiral

Aim of this project it to provide file-manager as close to MidnightCommander (MC) as possible with GTK-ui.
Project is in developement stage. Everyone is welcome to participate.

### The most important things are: 
1. keep keybindings as close to MC as possible
2. Do every operation asynchrionously no ui blocking

What features should version 1.0 have
1) Browsing files async
2) Quick Search
3) Copying / Moving
4) Directory creation
5) Quick View
6) Colouring based on mc.ini
7) Find option
8) Configuration window: categories on the left searchable, modfied panels become marked blue on left


Build requires gtkmm-3.0

### Building from CLI
```
cmake -E make_directory build 
cmake -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel --config Release
```

[![CMake](https://github.com/Krandelbord/file-fleet-admiral/actions/workflows/cmake.yml/badge.svg)](https://github.com/Krandelbord/file-fleet-admiral/actions/workflows/cmake.yml)
