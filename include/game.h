#ifndef GAME_H
#define GAME_H

#include "renderer.h"

#define GAME_ACTIVE_TICK 1
#define GAME_DISABLED_TICK 0

typedef struct {
    int is_active;
    int target_frame_rate;
} tick_context_t;

// Will return '0' on success.
int game_tryInitialize(window_context_t window_context, render_context_t* render_context);
void game_tick(tick_context_t* tick_context, const render_context_t* render_context);
void game_quit(render_context_t* render_context);

#endif // GAME_H
