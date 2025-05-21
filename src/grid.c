#include "grid.h"
#include <SDL3/SDL.h>
#include <assert.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>

void Grid_Initialize(struct node* grid) {
    assert(grid != NULL);

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            const int index = j * GRID_WIDTH + i;
            grid[index].x = i * NODE_SIZE;
            grid[index].y = j * NODE_SIZE;
            grid[index].state = 0;
        }
    }
}

struct node* Grid_FindAvailableNodes(const struct node* grid, const int* snake, int* length) {
    struct node* result = malloc(sizeof(struct node) * GRID_WIDTH * GRID_HEIGHT);
    if (result == NULL) {
        printf("Couldn't allocate memory to find available nodes\n");
        *length = 0;
        return NULL;
    }

    int internalLength = 0;
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (snake[i] == 0) {
            result[internalLength] = grid[i];
            internalLength++;
        }
    }

    struct node* strictBuffer = realloc(result, internalLength * sizeof(struct node));
    if (strictBuffer == NULL) {
        free(result);
        *length = 0;
        return NULL;
    }

    *length = internalLength;
    return strictBuffer;
}

void Grid_Render(const struct node* grid, const struct render_context* rndCtx) {
    assert(grid != NULL);
    assert(rndCtx != NULL);

    SDL_SetRenderDrawColor(rndCtx->renderer, 169, 204, 117, 255);

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            const int index = j * GRID_WIDTH + i;
            const int x = grid[index].x;
            const int y = grid[index].y;

            // Render food.
            if (grid[index].state == -1) {
                SDL_FRect rect;
                rect.w = NODE_SIZE;
                rect.h = NODE_SIZE;
                rect.x = grid[index].x;
                rect.y = grid[index].y;
                SDL_SetRenderDrawColor(rndCtx->renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(rndCtx->renderer, &rect);
                SDL_SetRenderDrawColor(rndCtx->renderer, 169, 204, 117, 255);
            }

            // Horizontal lines.
            SDL_RenderLine(rndCtx->renderer, x, y, x + NODE_SIZE, y);
            SDL_RenderLine(rndCtx->renderer, x, y + NODE_SIZE, x + NODE_SIZE, y + NODE_SIZE);

            // Vertical lines.
            SDL_RenderLine(rndCtx->renderer, x, y, x, y + NODE_SIZE);
            SDL_RenderLine(rndCtx->renderer, x + NODE_SIZE, y, x + NODE_SIZE, y + NODE_SIZE);
        }
    }
}
