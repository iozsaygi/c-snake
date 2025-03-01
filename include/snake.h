#ifndef SNAKE_H
#define SNAKE_H

#include "grid.h"

enum movement_direction { MD_UP, MD_RIGHT, MD_LEFT, MD_DOWN };
enum collision_state { CS_NONE, CS_FOOD, CS_SELF, CS_OOM };

void Snake_Initialize(int* snake);
int Snake_FindHeadIndex(const int* snake);
int Snake_FindTailIndex(const int* snake);
enum collision_state Snake_Update(enum movement_direction movementDirection, int* snake, int lastFoodGridIndex);
void Snake_Render(const struct render_context* rndCtx, const struct node* grid, const int* snake);

#endif // SNAKE_H
