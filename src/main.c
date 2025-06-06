#include "game.h"
#include "grid.h"
#include "renderer.h"

int main(int argc, const char* argv[]) {
    printf("[MAIN] CSnake Main\n");

    const window_context_t window_context = {
        640, // width
        480, // height
        "Classic Snake" // title
    };

    render_context_t render_context = {
        NULL, // window
        NULL // renderer
    };

    if (game_tryInitialize(window_context, &render_context) != 0) return -1;

    const grid_context_t grid_context = {
        32, // width
        24, // height
        20 // node_scale
    };

    // Stack allocated grid.
    node_t grid[grid_context.width * grid_context.height];

    grid_create(grid_context, grid);

    snake_t* snake = NULL;
    const snake_spawn_context_t snake_spawn_context = {
        230, // first_spawn_id
        231, // second_spawn_id
        232, // third_spawn_id
        3 // initial_length
    };

    const snake_body_simulation_context_t snake_body_simulation_context = {
        1000 // simulation_rate
    };

    snake_initialize(&snake, snake_spawn_context, grid);

    tick_context_t tick_context = {
        GAME_ACTIVE_TICK, // is_active
        60 // target_frame_rate
    };

    game_tick(&tick_context, &render_context, grid_context, grid, snake_body_simulation_context, snake);
    game_quit(&render_context);

    return 0;
}
