#include "grid.h"
#include <stdlib.h>
#include "renderer.h"

const color_t grid_color = {
    255, // r
    255, // g
    255, // b
    255 // a
};

void grid_create(const grid_context_t grid_context, node_t* grid) {
    for (int i = 0; i < grid_context.width; i++) {
        for (int j = 0; j < grid_context.height; j++) {
            const int index = j * grid_context.width + i;

            grid[index].id = index;

            const point_t position = {
                (float) i * grid_context.node_scale, // x
                (float) j * grid_context.node_scale // y
            };

            grid[index].position = position;
            grid[index].state = NODE_STATE_EMPTY;
        }
    }
}

void grid_render(const grid_context_t grid_context, const render_context_t* render_context, const node_t* grid) {
    for (int i = 0; i < grid_context.width * grid_context.height; i++) {
        const float x = grid[i].position.x;
        const float y = grid[i].position.y;

        // Horizontal lines, first pass.
        {
            const point_t origin = {
                x, // x
                y // y
            };

            const point_t destination = {
                x + grid_context.node_scale, // x
                y // y
            };

            // Horizontal lines.
            renderer_renderLineBetween(render_context, origin, destination, grid_color);
        }

        // Horizontal lines, second pass.
        {
            const point_t origin = {
                x, // x
                y + grid_context.node_scale // y
            };

            const point_t destination = {
                x + grid_context.node_scale, // x
                y + grid_context.node_scale // y
            };

            renderer_renderLineBetween(render_context, origin, destination, grid_color);
        }

        // Vertical lines, first pass.
        {
            const point_t origin = {
                x, // x
                y // y
            };

            const point_t destination = {
                x + grid_context.node_scale, // x
                y // y
            };

            renderer_renderLineBetween(render_context, origin, destination, grid_color);
        }

        // Vertical lines, second pass.
        {
            const point_t origin = {
                x + grid_context.node_scale, // x
                y // y
            };

            const point_t destination = {
                x + grid_context.node_scale, // x
                y + grid_context.node_scale // y
            };

            renderer_renderLineBetween(render_context, origin, destination, grid_color);
        }
    }
}

node_t* grid_findEmptyNodes(const grid_context_t grid_context, const node_t* grid, int* length) {
    int number_of_empty_nodes = 0;

    for (int i = 0; i < grid_context.width * grid_context.height; i++) {
        if (grid[i].state == NODE_STATE_EMPTY) number_of_empty_nodes++;
    }

    node_t* empty_nodes = (node_t*) malloc(sizeof(node_t) * number_of_empty_nodes);
    if (empty_nodes == NULL) {
        printf("[ERROR] Failed to allocate memory to find empty nodes within the grid\n");
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < grid_context.width * grid_context.height; i++) {
        if (grid[i].state == NODE_STATE_EMPTY) {
            empty_nodes[index++] = grid[i];
        }
    }

    *length = number_of_empty_nodes;
    return empty_nodes;
}
