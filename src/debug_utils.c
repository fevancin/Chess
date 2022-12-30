#include "header/debug_utils.h"

void print_debug_info(Game *game) {
    if (game == NULL) return;
    Index index = 0;
    Piece piece;
    for (index = 0; index < PIECES_NUM; index++) {
        piece = game->pieces[index];
        printf("%d: (%c%c) alive: %d promoted: %d\n",
            index,
            to_column_char(get_y(piece)),
            to_row_char(get_x(piece)),
            is_alive(piece),
            is_promoted(piece)
        );
    }
    printf("Turn of ");
    if (get_turn(game) == WHITE) printf("WHITE\n");
    else printf("BLACK\n");
}