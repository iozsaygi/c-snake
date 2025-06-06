#include "renderer.h"

int main(int argc, const char* argv[]) {
    printf("CSnake Main\n");

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

    return 0;
}
