#ifndef FOOD_H
#define FOOD_H

#include "grid.h"
#include "renderer.h"

extern const point_t food_size;
extern const color_t food_color;

void food_spawn(grid_context_t grid_context, node_t* grid);

#endif // FOOD_H
