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

    tick_context_t tick_context = {
        GAME_ACTIVE_TICK, // is_active
        30 // target_frame_rate
    };

    game_tick(&tick_context, &render_context, grid_context, grid);
    game_quit(&render_context);

    return 0;
}
