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

extern const point_t snake_body_segment_size;
extern const color_t snake_body_color;

struct snake_body_segment* snake_createBodySegment(int id);
void snake_initialize(snake_t** snake, snake_spawn_context_t snake_spawn_context);
void snake_append(snake_t* snake, struct snake_body_segment* segment);
void snake_render(const render_context_t* render_context, const snake_t* snake, const node_t* grid);
void snake_free(snake_t* snake);

#endif // SNAKE_H
