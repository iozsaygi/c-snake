#include "game.h"
#include "renderer.h"

int main(int argc, const char* argv[]) {
    printf("[MAIN] CSnake Main\n");

    window_context_t window_context = {
        640, // width
        480, // height
        30, // target_frame_rate
        "Classic Snake" // title
    };

    render_context_t render_context = {
        NULL, // window
        NULL // renderer
    };

    if (game_tryInitialize(window_context, &render_context) != 0) return -1;

    tick_context_t tick_context = {
        GAME_ACTIVE_TICK // is_active
    };

    game_tick(&tick_context, &render_context);
    game_quit(&render_context);

    return 0;
}
