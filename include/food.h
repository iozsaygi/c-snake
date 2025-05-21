#ifndef FOOD_H
#define FOOD_H

#include "grid.h"

int Food_Place(struct node* grid, const int* snake);
void Food_RemoveAt(struct node* grid, int index);

#endif // FOOD_H
