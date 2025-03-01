#include "snake.h"
#include <assert.h>
#include <grid.h>

void Snake_Initialize(int* snake) {
    assert(snake != NULL);

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        snake[i] = 0;
    }

    snake[270] = 1;
    snake[271] = 1;
    snake[272] = 1;
}

void Snake_Update(const int direction, int* snake) {
    // Find the head and tail.
    int headIndex = 0;
    int tailIndex = 0;

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] == 0) continue;
        if (snake[i + 1] == 0) headIndex = i;
        if (snake[i - 1] == 0) tailIndex = i;
    }

    snake[tailIndex] = 0;
    snake[headIndex + 1] = 1;
}

void Snake_Render(const struct render_context* rndCtx, const struct node* grid, const int* snake) {
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] == 0) continue;
        SDL_FRect rect;
        rect.w = NODE_SIZE;
        rect.h = NODE_SIZE;
        rect.x = grid[i].x;
        rect.y = grid[i].y;
        SDL_SetRenderDrawColor(rndCtx->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(rndCtx->renderer, &rect);
    }
}
