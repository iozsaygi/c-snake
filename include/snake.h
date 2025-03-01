#ifndef SNAKE_H
#define SNAKE_H

#include "grid.h"

void Snake_Initialize(int* snake);
void Snake_Render(const struct render_context* rndCtx, const struct node* grid, const int* snake);

#endif // SNAKE_H
