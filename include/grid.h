#ifndef GRID_H
#define GRID_H

#define GRID_WIDTH 32
#define GRID_HEIGHT 24
#define NODE_SIZE 20

#include "game.h"

struct node {
    int x;
    int y;
};

void Grid_Initialize(struct node* grid);
void Grid_Render(const struct node* grid, const struct render_context* rndCtx);

#endif // GRID_H
