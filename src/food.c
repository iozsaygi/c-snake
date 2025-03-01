#include "food.h"
#include <stdlib.h>
#include <time.h>

#include "grid.h"

void Food_Place(struct node* grid, const int* snake) {
    int length = 0;
    struct node* availableNodes = Grid_FindAvailableNodes(grid, snake, &length);

    // TODO: Maybe replace 'return' with a log?
    if (availableNodes == NULL) return;

    srand(time(NULL));

    const int minimum = 0;
    const int maximum = length;

    const int randomFoodIndex = rand() % (maximum - minimum + 1) + minimum;

    grid[randomFoodIndex].state = -1;

    free(availableNodes);
}
