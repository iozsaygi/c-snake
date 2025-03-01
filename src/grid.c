#include "grid.h"
#include <SDL3/SDL.h>
#include <assert.h>
#include <game.h>

void Grid_Initialize(struct node* grid) {
    assert(grid != NULL);

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            const int index = j * GRID_WIDTH + i;
            grid[index].x = i * NODE_SIZE;
            grid[index].y = j * NODE_SIZE;
        }
    }
}

void Grid_Render(const struct node* grid, const struct render_context* rndCtx) {
    assert(grid != NULL);
    assert(rndCtx != NULL);

    SDL_SetRenderDrawColor(rndCtx->renderer, 40, 40, 40, 255);

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            const int index = j * GRID_WIDTH + i;
            const int x = grid[index].x;
            const int y = grid[index].y;

            // Horizontal lines.
            SDL_RenderLine(rndCtx->renderer, x, y, x + NODE_SIZE, y);
            SDL_RenderLine(rndCtx->renderer, x, y + NODE_SIZE, x + NODE_SIZE, y + NODE_SIZE);

            // Vertical lines.
            SDL_RenderLine(rndCtx->renderer, x, y, x, y + NODE_SIZE);
            SDL_RenderLine(rndCtx->renderer, x + NODE_SIZE, y, x + NODE_SIZE, y + NODE_SIZE);
        }
    }
}
