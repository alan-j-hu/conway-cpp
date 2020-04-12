# Conway's Game of Life

Despite how iconic Conway's Game of Life is, I've never implemented it until
now. I wrote this program to commemorate the life of John Conway.

I wrote this program in C++17 using the SDL2 library. I use CMake to build.

How to build and run:

    mkdir .build
    cd .build
    cmake init ../
    make
    ./conway

To pause/play the game, press the space bar. While the game is paused, you can
click the cells to flip their state.
