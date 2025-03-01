#include "game.h"

int main(int argc, char* argv[]) {
    const struct window_context wndCtx = {
        640, // width
        480, // height
        60, // targetFrameRate
        "CSnake" // title
    };

    struct render_context rndCtx = {
        NULL, // renderer
        NULL // window
    };

    if (Game_TryCreate(&wndCtx, &rndCtx) != 0) return -1;

    Game_Update(&wndCtx, &rndCtx);
    Game_Shutdown(&rndCtx);

    return 0;
}
