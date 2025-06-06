#include "snake.h"
#include <stdlib.h>

const point_t snake_body_segment_size = {
    20, // x
    20 // y
};

const color_t snake_body_color = {
    60, // r
    60, // g
    60, // b
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

void snake_initialize(snake_t** snake, const snake_spawn_context_t snake_spawn_context, node_t* grid) {
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

    grid[(*snake)->tail->id].state = NODE_STATE_SNAKE;
    grid[center->id].state = NODE_STATE_SNAKE;
    grid[head->id].state = NODE_STATE_SNAKE;
}

void snake_append(snake_t* snake, struct snake_body_segment* segment, node_t* grid) {
    snake->head->next = segment;
    segment->next = NULL;
    segment->previous = snake->head;
    snake->head = segment;
    snake->length++;

    grid[segment->id].state = NODE_STATE_SNAKE;
}

struct snake_body_segment* snake_removeTail(snake_t* snake, node_t* grid) {
    struct snake_body_segment* current_tail = snake->tail;

    snake->tail = current_tail->next;
    snake->tail->previous = NULL;

    grid[current_tail->id].state = NODE_STATE_EMPTY;

    return current_tail;
}

int snake_predictNextGridIndexBasedOnDirection(const snake_t* snake, const grid_context_t grid_context,
                                               const snake_direction_t direction) {
    const int head_id = snake->head->id;
    int x = head_id % grid_context.width;
    int y = head_id / grid_context.width;

    switch (direction) {
        case SNAKE_DIRECTION_NORTH:
            y = (y - 1 + grid_context.height) % grid_context.height;
            break;
        case SNAKE_DIRECTION_SOUTH:
            y = (y + 1) % grid_context.height;
            break;
        case SNAKE_DIRECTION_WEST:
            x = (x - 1 + grid_context.width) % grid_context.width;
            break;
        case SNAKE_DIRECTION_EAST:
            x = (x + 1) % grid_context.width;
            break;
    }

    return y * grid_context.width + x;
}


void snake_simulate(snake_t* snake, const grid_context_t grid_context, node_t* grid,
                    const snake_direction_t snake_direction) {
    struct snake_body_segment* current_tail = snake_removeTail(snake, grid);
    const int index_prediction = snake_predictNextGridIndexBasedOnDirection(snake, grid_context, snake_direction);
    current_tail->id = index_prediction;
    snake_append(snake, current_tail, grid);
}

// void snake_render(const render_context_t* render_context, const snake_t* snake, const node_t* grid) {
//     const struct snake_body_segment* current = snake->tail;
//
//     while (current != NULL) {
//         const node_t node = grid[current->id];
//         renderer_renderFullRectangleAt(render_context, node.position, snake_body_segment_size, snake_body_color);
//
//         current = current->next;
//     }
// }

void snake_free(snake_t* snake) {
    struct snake_body_segment* current = snake->tail;

    while (current != NULL) {
        struct snake_body_segment* next = current->next;
        free(current);
        current = next;
    }

    free(snake);
}
