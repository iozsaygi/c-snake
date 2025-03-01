#include "snake.h"
#include <assert.h>
#include <grid.h>

void Snake_Initialize(int* snake) {
    assert(snake != NULL);

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        snake[i] = 0;
    }

    snake[265] = 1;
    snake[266] = 2;
    snake[267] = 3;
}

int Snake_FindHeadIndex(const int* snake) {
    assert(snake != NULL);

    int headIndex = -1;
    int maximumValue = -1;

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] > maximumValue) {
            maximumValue = snake[i];
            headIndex = i;
        }
    }

    return headIndex;
}

int Snake_FindTailIndex(const int* snake) {
    assert(snake != NULL);

    int tailIndex = -1;
    int minimumValue = GRID_WIDTH * GRID_HEIGHT + 1;

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] < minimumValue && snake[i] > 0) {
            minimumValue = snake[i];
            tailIndex = i;
        }
    }

    return tailIndex;
}

enum collision_state Snake_Update(const enum movement_direction movementDirection, int* snake, int lastFoodGridIndex) {
    // index + GRID_WIDTH = Downward node.
    // index + 1 = Right node.
    // index - GRID_WIDTH = Upper node.
    // index - 1 = Left node.

    const int headIndex = Snake_FindHeadIndex(snake);
    const int tailIndex = Snake_FindTailIndex(snake);

    int newHeadIndex = 0;

    switch (movementDirection) {
        case MD_UP:
            newHeadIndex = headIndex - GRID_WIDTH;
            break;
        case MD_LEFT:
            newHeadIndex = headIndex - 1;
            break;
        case MD_DOWN:
            newHeadIndex = headIndex + GRID_WIDTH;
            break;
        case MD_RIGHT:
            newHeadIndex = headIndex + 1;
            break;
        default:
            break;
    }

    snake[newHeadIndex] = snake[headIndex] + 1;
    snake[tailIndex] = 0;

    if (newHeadIndex == lastFoodGridIndex) return CS_FOOD;

    return CS_NONE;
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
