#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(int argc, char* argv[]) {
    const struct window_context wndCtx = {
        640, // width
        480, // height
        60, // targetFrameRate
        "Classic Snake" // title
    };

    struct render_context rndCtx = {
        NULL, // renderer
        NULL // window
    };

    // Set the seed now instead of setting it each time before food placement.
    srand(time(NULL));

    if (Game_TryCreate(&wndCtx, &rndCtx) != 0) return -1;

    Game_Update(&wndCtx, &rndCtx);
    Game_Shutdown(&rndCtx);

    return 0;
}
