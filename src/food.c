#include "food.h"
#include <stdlib.h>
#include <time.h>

#include "grid.h"

int Food_Place(struct node* grid, const int* snake) {
    int length = 0;
    struct node* availableNodes = Grid_FindAvailableNodes(grid, snake, &length);

    // TODO: Maybe replace 'return' with a log?
    if (availableNodes == NULL) return 0;

    // srand(time(NULL));

    const int minimum = 0;
    const int maximum = length;

    const int randomFoodIndex = rand() % length;

    grid[randomFoodIndex].state = -1;

    free(availableNodes);

    return randomFoodIndex;
}

void Food_RemoveAt(struct node* grid, int index) {
    if (index != -1) grid[index].state = 0;
}
