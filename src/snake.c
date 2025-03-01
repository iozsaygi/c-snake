#include "snake.h"
#include <assert.h>
#include <grid.h>

void Snake_Initialize(int* snake) {
    assert(snake != NULL);

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        snake[i] = 0;
    }

    snake[260] = 1;
    snake[261] = 1;
    snake[262] = 1;
}

void Snake_Update(const enum movement_direction movementDirection, int* snake) {
    // index + GRID_WIDTH = Downward node.
    // index + 1 = Right node.
    // index - GRID_WIDTH = Upper node.
    // index - 1 = Left node.

    // Find the head and tail.
    int headIndex = 0;
    int tailIndex = 0;

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] == 0) continue;

        if (movementDirection == MD_RIGHT) {
            if (snake[i + 1] == 0) headIndex = i;
            if (snake[i - 1] == 0) tailIndex = i;
        } else if (movementDirection == MD_LEFT) {
            if (snake[i + 1] == 1 && snake[i - 1] == 0) tailIndex = i;
            if (snake[i + 1] == 0) headIndex = i;
        }
    }

    if (movementDirection == MD_RIGHT) {
        snake[tailIndex] = 0;
        snake[headIndex + 1] = 1;
    } else if (movementDirection == MD_LEFT) {
        snake[tailIndex - 1] = 1;
        snake[headIndex] = 0;
    }
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
