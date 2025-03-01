#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

struct window_context {
    int width;
    int height;
    const char* title;
};

struct render_context {
    SDL_Renderer* renderer;
    SDL_Window* window;
};

int Game_TryCreate(const struct window_context* wndCtx, struct render_context* rndCtx);
void Game_Shutdown(struct render_context* rndCtx);

#endif // GAME_H
