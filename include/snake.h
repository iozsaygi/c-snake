#ifndef SNAKE_H
#define SNAKE_H

#include "grid.h"

enum movement_direction { MD_UP, MD_RIGHT, MD_LEFT, MD_DOWN };

void Snake_Initialize(int* snake);
void Snake_Update(enum movement_direction movementDirection, int* snake);
void Snake_Render(const struct render_context* rndCtx, const struct node* grid, const int* snake);

#endif // SNAKE_H
