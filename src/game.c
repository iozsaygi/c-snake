#include "game.h"
#include "SDL3/SDL_init.h"

int game_tryInitialize(const window_context_t window_context, render_context_t* render_context) {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("[ERROR] Failed to initialize SDL, the reason was %s\n", SDL_GetError());
        return -1;
    }

    render_context->window = SDL_CreateWindow(window_context.title, window_context.width, window_context.height, 0);
    if (render_context->window == NULL) {
        printf("[ERROR] Failed to create game window, the reason was %s\n", SDL_GetError());
        return -1;
    }

    render_context->renderer = SDL_CreateRenderer(render_context->window, NULL);
    if (render_context->renderer == NULL) {
        printf("[ERROR] Failed to create renderer, the reason was %s\n", SDL_GetError());
        return -1;
    }

    printf("[GAME] Successfully initialized the game context\n");

    return 0;
}

void game_tick(tick_context_t* tick_context, const render_context_t* render_context, grid_context_t grid_context,
               const node_t* grid) {
    SDL_Event event;

    while (tick_context->is_active == GAME_ACTIVE_TICK) {

        // Event handling.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    tick_context->is_active = GAME_DISABLED_TICK;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            tick_context->is_active = GAME_DISABLED_TICK;
                            break;
                        default:
                    }
                default:
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(render_context->renderer, renderer_background_color.r, renderer_background_color.g,
                               renderer_background_color.b, renderer_background_color.a);
        SDL_RenderClear(render_context->renderer);

        grid_render(grid_context, render_context, grid);

        SDL_RenderPresent(render_context->renderer);
    }
}

void game_quit(render_context_t* render_context) {
    SDL_DestroyRenderer(render_context->renderer);
    SDL_DestroyWindow(render_context->window);
    render_context->window = NULL;
    render_context->renderer = NULL;
    SDL_Quit();

    printf("[GAME] Successfully cleaned up game context\n");
}
