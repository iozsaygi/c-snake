#include "game.h"
#include <assert.h>
#include <stdio.h>
#include "food.h"
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

    printf("[GAME] Successfully created platform layer\n");

    return 0;
}

void Game_Update(const struct window_context* wndCtx, const struct render_context* rndCtx) {
    // Create grid.
    struct node grid[GRID_WIDTH * GRID_HEIGHT];
    Grid_Initialize(grid);

    printf("[GAME] Initialized grid data\n");

    // Create snake body.
    int snake[GRID_WIDTH * GRID_HEIGHT];
    Snake_Initialize(snake);

    // Initialize snake movement direction.
    enum movement_direction movementDirection = MD_RIGHT;
    printf("[GAME] Initialized snake data\n");

    // Initialize the food.
    Food_Place(grid, snake);
    printf("[GAME] Initialized food data\n");

    int isActive = 1;
    SDL_Event event;

    const uint32_t frameDelay = 1000 / wndCtx->targetFrameRate;
    uint32_t lastSimulationTime = SDL_GetTicks();
    uint32_t currentTime = 0;
    uint32_t frameStart = 0;
    const uint32_t simulationRate = 500;

    printf("[GAME] Entering the update loop\n");

    while (isActive == 1) {
        frameStart = SDL_GetTicks();

        // Event handling.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isActive = 0;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_W) {
                        movementDirection = MD_UP;
                    } else if (event.key.key == SDLK_A) {
                        movementDirection = MD_LEFT;
                    } else if (event.key.key == SDLK_S) {
                        movementDirection = MD_DOWN;
                    } else if (event.key.key == SDLK_D) {
                        movementDirection = MD_RIGHT;
                    }
                    break;
                default:;
            }
        }

        currentTime = SDL_GetTicks();
        if (currentTime - lastSimulationTime >= simulationRate) {
            printf("[GAME] Simulation tick\n");
            lastSimulationTime = currentTime;

            Snake_Update(movementDirection, snake);
        }

        // Render scene.
        SDL_SetRenderDrawColor(rndCtx->renderer, 0, 0, 0, 255);
        SDL_RenderClear(rndCtx->renderer);

        Grid_Render(grid, rndCtx);
        Snake_Render(rndCtx, grid, snake);

        SDL_RenderPresent(rndCtx->renderer);

        const uint32_t frameDuration = SDL_GetTicks() - frameStart;
        if (frameDuration < frameDelay) {
            SDL_Delay(frameDelay - frameDuration);
        }
    }
    printf("[GAME] Exiting the update loop\n");
}


void Game_Shutdown(struct render_context* rndCtx) {
    printf("[GAME] Shutting down and clearing allocated resources\n");

    SDL_DestroyRenderer(rndCtx->renderer);
    SDL_DestroyWindow(rndCtx->window);

    rndCtx->renderer = NULL;
    rndCtx->window = NULL;

    SDL_Quit();
}
