#include "food.h"
#include <stdlib.h>

const point_t food_size = {
    20, // x
    20 // y
};

const color_t food_color = {
    255, // r
    255, // g
    255, // b
    255 // a
};

void food_spawn(grid_context_t grid_context, node_t* grid) {
    int length;
    node_t* empty_nodes = grid_findEmptyNodes(grid_context, grid, &length);

    const int food_index = rand() % length;

    grid[food_index].state = NODE_STATE_FOOD;

    free(empty_nodes);
}
