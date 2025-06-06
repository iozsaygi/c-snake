#ifndef RENDERER_H
#define RENDERER_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "point.h"

// Basic properties of game window.
typedef struct {
    int width;
    int height;
    const char* title;
} window_context_t;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} render_context_t;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} color_t;

extern const color_t renderer_background_color;

void renderer_renderRectangleAt(const render_context_t* render_context, point_t at, point_t size, color_t color);

#endif // RENDERER_H
