#include "utils.h"

typedef struct move {
    Type piece_type;
    Coordinate row_from;
    Coordinate column_from;
    Coordinate row_to;
    Coordinate column_to;
} Move;

void empty_move(Move *move);

int is_valid_move(Move *move);