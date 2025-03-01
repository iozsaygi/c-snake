#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Couldn't initialize SDL, the reason was: %s", SDL_GetError());
        return -1;
    }

    SDL_Quit();
    return 0;
}
