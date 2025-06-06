#include "snake.h"
#include <stdlib.h>

const point_t snake_body_segment_size = {
    20, // x
    20 // y
};

const color_t snake_body_color = {
    255, // r
    255, // g
    255, // b
    255 // a
};

struct snake_body_segment* snake_createBodySegment(const int id) {
    // ReSharper disable once CppDFAMemoryLeak
    struct snake_body_segment* segment = (struct snake_body_segment*) malloc(sizeof(struct snake_body_segment));
    if (segment == NULL) {
        printf("[ERROR] Failed to allocate memory for snake body segment\n");
        return NULL;
    }

    segment->id = id;
    segment->next = NULL;
    segment->previous = NULL;

    return segment;
}

void snake_initialize(snake_t** snake, const snake_spawn_context_t snake_spawn_context) {
    *snake = (snake_t*) malloc(sizeof(snake_t));
    if (*snake == NULL) {
        printf("[ERROR] Failed to allocate memory for snake\n");
        return;
    }

    (*snake)->tail = snake_createBodySegment(snake_spawn_context.first_spawn_id);
    (*snake)->tail->previous = NULL;

    struct snake_body_segment* center = snake_createBodySegment(snake_spawn_context.second_spawn_id);
    (*snake)->tail->next = center;
    center->previous = (*snake)->tail;

    struct snake_body_segment* head = snake_createBodySegment(snake_spawn_context.third_spawn_id);
    center->next = head;
    head->previous = center;
    head->next = NULL;

    (*snake)->head = head;
    (*snake)->length = snake_spawn_context.initial_length;
}

void snake_append(snake_t* snake, struct snake_body_segment* segment) {
    snake->head->next = segment;
    segment->next = NULL;
    segment->previous = snake->head;
    snake->head = segment;
    snake->length++;
}

void snake_render(const render_context_t* render_context, const snake_t* snake, const node_t* grid) {
    const struct snake_body_segment* current = snake->tail;

    while (current != NULL) {
        const node_t node = grid[current->id];
        renderer_renderFullRectangleAt(render_context, node.position, snake_body_segment_size, snake_body_color);

        current = current->next;
    }
}

void snake_free(snake_t* snake) {
    struct snake_body_segment* current = snake->tail;

    while (current != NULL) {
        struct snake_body_segment* next = current->next;
        free(current);
        current = next;
    }

    free(snake);
}
