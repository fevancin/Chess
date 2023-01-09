#include "value.h"

// depth of the search
#define MAX_DEPTH 3

// search routine that calculate the best move found
// starting in a certain position. Returns the value of that choice.
Value search(Game *game, Move *best_move);