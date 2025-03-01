#include "game.h"
#include <assert.h>
#include <stdio.h>

int Game_TryCreate(const struct window_context* wndCtx, struct render_context* rndCtx) {
    assert(wndCtx != NULL);
    assert(rndCtx != NULL);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Could not initialize SDL, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rndCtx->window = SDL_CreateWindow(wndCtx->title, wndCtx->width, wndCtx->height, SDL_WINDOWPOS_CENTERED);
    if (rndCtx->window == NULL) {
        printf("Could not create SDL window, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rndCtx->renderer = SDL_CreateRenderer(rndCtx->window, NULL);
    if (rndCtx->renderer == NULL) {
        printf("Could not create SDL renderer, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Delay(3000);

    return 0;
}

void Game_Shutdown(struct render_context* rndCtx) {
    SDL_DestroyRenderer(rndCtx->renderer);
    SDL_DestroyWindow(rndCtx->window);

    rndCtx->renderer = NULL;
    rndCtx->window = NULL;

    SDL_Quit();
}
