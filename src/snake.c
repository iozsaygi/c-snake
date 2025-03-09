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

enum collision_state Snake_Update(const enum movement_direction movementDirection, int* snake,
                                  const int lastFoodGridIndex) {
    const int headIndex = Snake_FindHeadIndex(snake);
    const int tailIndex = Snake_FindTailIndex(snake);

    int newHeadIndex = headIndex;

    // Setting new head index by considering edge wrapping.
    // This lets us avoid the case where snake can move out of window/grid.
    switch (movementDirection) {
        case MD_UP:
            newHeadIndex = headIndex < GRID_WIDTH ? headIndex + GRID_WIDTH * (GRID_HEIGHT - 1) : headIndex - GRID_WIDTH;
            break;
        case MD_LEFT:
            newHeadIndex = headIndex % GRID_WIDTH == 0 ? headIndex + (GRID_WIDTH - 1) : headIndex - 1;
            break;
        case MD_DOWN:
            newHeadIndex =
                headIndex >= GRID_WIDTH * (GRID_HEIGHT - 1) ? (headIndex % GRID_WIDTH) : headIndex + GRID_WIDTH;
            break;
        case MD_RIGHT:
            newHeadIndex = headIndex % GRID_WIDTH == GRID_WIDTH - 1 ? headIndex - (GRID_WIDTH - 1) : headIndex + 1;
            break;
        default:
            break;
    }

    if (snake[newHeadIndex] != 0) {
        return CS_SELF;
    }

    if (newHeadIndex == lastFoodGridIndex) {
        snake[newHeadIndex] = snake[headIndex] + 1;
        return CS_FOOD;
    }

    snake[newHeadIndex] = snake[headIndex] + 1;
    snake[tailIndex] = 0;

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
        SDL_SetRenderDrawColor(rndCtx->renderer, 60, 60, 60, 255);
        SDL_RenderFillRect(rndCtx->renderer, &rect);
    }
}
