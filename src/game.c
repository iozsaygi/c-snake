#include "game.h"
#include <assert.h>
#include <stdio.h>

int Game_TryCreate(const struct window_context* wndCtx, struct render_context* rndCtx) {
    assert(wndCtx != NULL);
    assert(rndCtx != NULL);

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("Could not initialize SDL, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rndCtx->window = SDL_CreateWindow(wndCtx->title, wndCtx->width, wndCtx->height, 0);
    if (rndCtx->window == NULL) {
        printf("Could not create SDL window, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rndCtx->renderer = SDL_CreateRenderer(rndCtx->window, NULL);
    if (rndCtx->renderer == NULL) {
        printf("Could not create SDL renderer, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

void Game_Update(const struct render_context* rndCtx) {
    int isActive = 1;
    SDL_Event event;

    while (isActive == 1) {
        // Event handling.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isActive = 0;
                    break;
                default:;
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(rndCtx->renderer, 0, 0, 0, 255);
        SDL_RenderClear(rndCtx->renderer);

        // TODO: Render calls goes here.

        SDL_RenderPresent(rndCtx->renderer);
    }
}

void Game_Shutdown(struct render_context* rndCtx) {
    SDL_DestroyRenderer(rndCtx->renderer);
    SDL_DestroyWindow(rndCtx->window);

    rndCtx->renderer = NULL;
    rndCtx->window = NULL;

    SDL_Quit();
}
