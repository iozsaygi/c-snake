#include "game.h"

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_timer.h"
#include "food.h"

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
               node_t* grid, snake_spawn_context_t snake_spawn_context,
               snake_body_simulation_context_t snake_body_simulation_context, snake_t* snake) {
    SDL_Event event;

    // Setup snake direction.
    snake_direction_t snake_direction = SNAKE_DIRECTION_EAST;

    // Spawn food before entering game loop.
    food_spawn(grid_context, grid);

    const int scalar = 1000;
    const Uint32 frame_delay = scalar / tick_context->target_frame_rate;

    uint32_t snake_body_last_simulation_registry = SDL_GetTicks();

    while (tick_context->is_active == GAME_ACTIVE_TICK) {
        const uint32_t snake_body_simulation_rate = snake_body_simulation_context.simulation_rate;
        const Uint32 frame_start = SDL_GetTicks();

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
                        case SDLK_W:
                            snake_direction = SNAKE_DIRECTION_NORTH;
                            break;
                        case SDLK_A:
                            snake_direction = SNAKE_DIRECTION_WEST;
                            break;
                        case SDLK_S:
                            snake_direction = SNAKE_DIRECTION_SOUTH;
                            break;
                        case SDLK_D:
                            snake_direction = SNAKE_DIRECTION_EAST;
                            break;
                        default:
                    }
                default:
            }
        }

        if (SDL_GetTicks() - snake_body_last_simulation_registry >= snake_body_simulation_rate) {
            // printf("[GAME] Simulating the snake body\n");
            snake_body_last_simulation_registry = SDL_GetTicks();

            const snake_simulation_result_t snake_simulation_result =
                snake_simulate(snake, grid_context, grid, snake_direction);

            switch (grid[snake_simulation_result.desired_node_id].state) {
                case NODE_STATE_EMPTY:
                    grid[snake_simulation_result.desired_node_id].state = NODE_STATE_SNAKE;
                    break;
                case NODE_STATE_SNAKE:
                    snake_direction = SNAKE_DIRECTION_EAST;
                    grid_reset(grid_context, grid);
                    snake_free(snake);
                    snake_initialize(&snake, snake_spawn_context, grid);
                    food_spawn(grid_context, grid);
                    break;
                case NODE_STATE_FOOD:
                    grid[snake_simulation_result.desired_node_id].state = NODE_STATE_SNAKE;
                    struct snake_body_segment* segment =
                        snake_createBodySegment(snake_simulation_result.desired_node_id);
                    snake_append(snake, segment);
                    food_spawn(grid_context, grid);

                    snake->length++;

                    printf("[GAME] Snake ate food, new body length is %d\n", snake->length);
                    break;
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(render_context->renderer, renderer_background_color.r, renderer_background_color.g,
                               renderer_background_color.b, renderer_background_color.a);
        SDL_RenderClear(render_context->renderer);

        grid_render(grid_context, render_context, grid);

        SDL_RenderPresent(render_context->renderer);

        const Uint32 current_frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > current_frame_time) {
            SDL_Delay(frame_delay - current_frame_time);
        }
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
