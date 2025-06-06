#ifndef GRID_H
#define GRID_H

#include "point.h"
#include "renderer.h"

typedef enum { NODE_STATE_EMPTY, NODE_STATE_SNAKE, NODE_STATE_FOOD } node_state_t;

typedef struct {
    int id;
    point_t position;
    node_state_t state;
} node_t;

typedef struct {
    int width;
    int height;
    int node_scale;
} grid_context_t;

extern const color_t grid_color;

void grid_create(grid_context_t grid_context, node_t* grid);
void grid_render(grid_context_t grid_context, const render_context_t* render_context, const node_t* grid);

#endif // GRID_H
