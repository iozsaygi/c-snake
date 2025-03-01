# Classic Snake

Grid-based snake game, which was created during a small Saturday (March 2, 2025) game development challenge within
several hours. I used MinGW to compile this for Windows, but it should require minimal effort to port this to other
compilers, such as MSVC.

This is also possible thanks to a
wonderful [lecture](https://www.kosbie.net/cmu/fall-10/15-110/handouts/snake/snake.html#:~:text=In%20the%20game%20of%20Snake,as%20possible%20before%20that%20happens.)
that is available on the internet, which explains the details of the grid-based snake game amazingly.

<p align="center">
    <img alt="Gameplay footage" src="https://github.com/iozsaygi/c-snake/blob/main/assets/gameplay.gif?raw=true">
</p>

There are still QoL improvements that I need to ship, such as a better random number generator and several other minor
gameplay bugs.

## Building

### Windows

#### MinGW

1. Download and install [CMake](https://cmake.org/)
2. Download and install [MinGW](https://sourceforge.net/projects/mingw/)
3. Add `MinGW` to path
4. Run `win32-build.bat`

## License

[MIT License](https://github.com/iozsaygi/c-snake/blob/main/LICENSE)
