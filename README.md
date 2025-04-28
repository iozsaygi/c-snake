# Classic Snake

Grid-based snake game, which was created during a small Saturday (March 02, 2025) game development challenge within
several hours. I used MinGW to compile this for Windows, but it should require minimal effort to port this to other
compilers, such as MSVC.

This is also possible thanks to a
wonderful [lecture](https://www.kosbie.net/cmu/fall-10/15-110/handouts/snake/snake.html#:~:text=In%20the%20game%20of%20Snake,as%20possible%20before%20that%20happens.)
that is available on the internet, which explains the details of the grid-based snake game amazingly.

There are still QoL improvements that I need to ship, such as a better random number generator and several other minor
gameplay bugs.

## Changelog

- macOS-specific update on April 28, 2025. The entire game has been ported to
  macOS. Click [here](https://github.com/iozsaygi/c-snake/commit/f9edf915b0a537853065e19c1cd98fee2cf35cc1) to visit
  related revision.

- Minimal update on March 27, 2025. Correcting the usage of `srand` when replacing the food around the grid.

- First update on March 09, 2025. Reworked the color palette to catch a nostalgic feel and added edge wrapping for
  enhanced gameplay.

<p align="center">
    <img alt="Gameplay footage" src="https://github.com/iozsaygi/c-snake/blob/main/assets/gameplay-first-update.gif?raw=true">
</p>

- Initial release on March 02, 2025.

<p align="center">
    <img alt="Gameplay footage" src="https://github.com/iozsaygi/c-snake/blob/main/assets/gameplay.gif?raw=true">
</p>

## Building

### Windows

#### MinGW

1. Download and install [CMake](https://cmake.org/)
2. Download and install [MinGW](https://sourceforge.net/projects/mingw/)
3. Add `MinGW` to path
4. Run `win32-build.bat`

### macOS

1. Install CMake via Homebrew `brew install cmake`
2. `chmod +x .build.sh` on the terminal to give build file required permissions
3. Run `build.sh`

## Configuring gameplay

If you wish to play around with several crucial aspects;

1. You can update the simulation speed however you want;
   visit [game.c](https://github.com/iozsaygi/c-snake/blob/main/src/game.c) and play around with `simulationRate`
2. Current keybindings are W, A, S, and D, but you can modify it however you like. Refer to
   the [game.c](https://github.com/iozsaygi/c-snake/blob/main/src/game.c)
3. You can also experiment with different grid sizes by
   visiting [grid.h](https://github.com/iozsaygi/c-snake/blob/main/include/grid.h)

## License

[MIT License](https://github.com/iozsaygi/c-snake/blob/main/LICENSE)
