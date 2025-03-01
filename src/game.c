#include "game.h"
#include <assert.h>
#include <stdio.h>
#include "grid.h"
#include "snake.h"

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

void Game_Update(const struct window_context* wndCtx, const struct render_context* rndCtx) {
    // Create grid.
    struct node grid[GRID_WIDTH * GRID_HEIGHT];
    Grid_Initialize(grid);

    // Create snake body.
    int snake[GRID_WIDTH * GRID_HEIGHT];
    Snake_Initialize(snake);

    int isActive = 1;
    SDL_Event event;

    const uint32_t frameDelay = 1000 / wndCtx->targetFrameRate;

    while (isActive == 1) {
        const uint32_t frameStart = SDL_GetTicks();

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

        Grid_Render(grid, rndCtx);
        Snake_Render(rndCtx, grid, snake);

        SDL_RenderPresent(rndCtx->renderer);

        const uint32_t frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game_Shutdown(struct render_context* rndCtx) {
    SDL_DestroyRenderer(rndCtx->renderer);
    SDL_DestroyWindow(rndCtx->window);

    rndCtx->renderer = NULL;
    rndCtx->window = NULL;

    SDL_Quit();
}
