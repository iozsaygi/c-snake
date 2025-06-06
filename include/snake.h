#ifndef SNAKE_H
#define SNAKE_H

#include "grid.h"
#include "renderer.h"

struct snake_body_segment {
    // This exactly matches the 'id' property of nodes within grid.
    int id;

    struct snake_body_segment* next;
    struct snake_body_segment* previous;
};

typedef struct {
    int length;
    struct snake_body_segment* head;
    struct snake_body_segment* tail;
} snake_t;

typedef struct {
    int first_spawn_id;
    int second_spawn_id;
    int third_spawn_id;
    int initial_length;
} snake_spawn_context_t;

typedef struct {
    int simulation_rate;
} snake_body_simulation_context_t;

typedef struct {
    int removed_node_id;
    int registered_node_id;
} snake_simulation_result_t;

typedef enum {
    SNAKE_DIRECTION_NORTH,
    SNAKE_DIRECTION_WEST,
    SNAKE_DIRECTION_SOUTH,
    SNAKE_DIRECTION_EAST,
} snake_direction_t;

extern const point_t snake_body_segment_size;
extern const color_t snake_body_color;

struct snake_body_segment* snake_createBodySegment(int id);
void snake_initialize(snake_t** snake, snake_spawn_context_t snake_spawn_context, node_t* grid);
void snake_append(snake_t* snake, struct snake_body_segment* segment, node_t* grid);
struct snake_body_segment* snake_removeTail(snake_t* snake, node_t* grid);

int snake_predictNextGridIndexBasedOnDirection(const snake_t* snake, grid_context_t grid_context,
                                               snake_direction_t direction);
snake_simulation_result_t snake_simulate(snake_t* snake, grid_context_t grid_context, node_t* grid,
                                         snake_direction_t snake_direction);

// Rendering based on node states instead, still keeping this for other cases.
// void snake_render(const render_context_t* render_context, const snake_t* snake, const node_t* grid);

void snake_free(snake_t* snake);

#endif // SNAKE_H
