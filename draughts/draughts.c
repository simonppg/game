#include "mocks.h"

#include "draughts.h"

struct Draughts *init_game(void)
{
    struct Draughts *game =
        (struct Draughts *) malloc(sizeof(struct Draughts));
    return game;
}
