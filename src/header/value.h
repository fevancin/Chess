#include "move.h"

// type of a game evaluation.
// big positive values mean better for WHITE,
// big negative values mean better for BLACK.
typedef double Value;

// returns an evaluation of the given game
Value get_game_value(Game *game);