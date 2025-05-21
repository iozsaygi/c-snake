#ifndef GRID_H
#define GRID_H

#define GRID_WIDTH 32
#define GRID_HEIGHT 24
#define NODE_SIZE 20

#include "game.h"

struct node {
    int x;
    int y;

    // Considering we are already storing snake's body with integer array.
    // This can represent empty node or node with food.
    // 0 = Empty, -1 = Food.
    int state;
};

void Grid_Initialize(struct node* grid);

struct node* Grid_FindAvailableNodes(const struct node* grid, const int* snake, int* length);

void Grid_Render(const struct node* grid, const struct render_context* rndCtx);

#endif // GRID_H
