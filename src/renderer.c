#include "renderer.h"

const color_t renderer_background_color = {
    149, // r
    194, // g
    107, // b
    255 // a
};

void renderer_renderFullRectangleAt(const render_context_t* render_context, const point_t at, const point_t size,
                                    const color_t color) {
    SDL_FRect render_rectangle;

    render_rectangle.x = at.x;
    render_rectangle.y = at.y;
    render_rectangle.w = size.x;
    render_rectangle.h = size.y;

    SDL_SetRenderDrawColor(render_context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render_context->renderer, &render_rectangle);
}

void renderer_renderLineBetween(const render_context_t* render_context, const point_t origin, const point_t destination,
                                const color_t color) {
    SDL_SetRenderDrawColor(render_context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(render_context->renderer, origin.x, origin.y, destination.x, destination.y);
}
