#include "game.h"

Color get_turn(Game *game) {
    return is_promoted(game->pieces[0]) ? BLACK : WHITE;
}
void set_turn(Game *game, Color color) {
    if (color == WHITE) depromote(&(game->pieces[0]));
    else promote(&(game->pieces[0]));
}
void swap_turn(Game *game) {
    if (is_promoted(game->pieces[0])) depromote(&(game->pieces[0]));
    else promote(&(game->pieces[0]));
}

int is_game_end(Game *game) {
    if (is_alive(game->pieces[0]) && is_alive(game->pieces[1])) return 0;
    return 1;
}

int is_piece(Game *game, Coordinate x, Coordinate y) {
    return game->board[x][y] != EMPTY;
}

void empty_game(Game *game) {
    memset(game->board, EMPTY, BOARD_DIM * BOARD_DIM);
    memset(game->pieces, (Piece)0, PIECES_NUM);
    set_turn(game, WHITE);
}

void place_piece(Game *game, Index index, Coordinate x, Coordinate y) {
    Piece *piece = &(game->pieces[index]);
    set_x(piece, x);
    set_y(piece, y);
    revive(piece);
    depromote(piece);
    game->board[x][y] = index;
}

void remove_piece(Game *game, Index i) {
    Piece p = game->pieces[i];
    game->board[get_x(p)][get_y(p)] = 0;
    kill(&(game->pieces[i]));
}

void move_piece(Game *game, Index index, Coordinate x, Coordinate y) {
    Index dest_index = game->board[x][y];
    if (dest_index != EMPTY) {
        kill(&(game->pieces[dest_index]));
    }
    Piece *piece = &(game->pieces[index]);
    game->board[get_x(*piece)][get_y(*piece)] = EMPTY;
    set_x(piece, x);
    set_y(piece, y);
    if ((x == BOARD_DIM - 1 || x == 0) && get_type(index) == PAWN) promote(piece);
    game->board[x][y] = index;
}

Position initial_configuration_map[32] = {
    {7, 4}, {0, 4},                                                 // kings
    {7, 3}, {0, 3},                                                 // queens
    {7, 0}, {0, 0}, {7, 7}, {0, 7},                                 // rooks
    {7, 1}, {0, 1}, {7, 6}, {0, 6},                                 // knights
    {7, 2}, {0, 2}, {7, 5}, {0, 5},                                 // bishops
    {6, 0}, {1, 0}, {6, 1}, {1, 1}, {6, 2}, {1, 2}, {6, 3}, {1, 3}, // pawns
    {6, 4}, {1, 4}, {6, 5}, {1, 5}, {6, 6}, {1, 6}, {6, 7}, {1, 7}
};

void place_initial_configuration(Game *game) {
    empty_game(game);
    Index index = 0;
    for (index = 0; index < PIECES_NUM; index++) {
        place_piece(game, index, initial_configuration_map[index].x, initial_configuration_map[index].y);
    }
}

void copy_game(Game *destination, Game *source) {
    memcpy(destination, source, sizeof(Game));
}

void print_game(Game *game) {
    if (game == NULL) return;
    int i = 0, j = 0;
    Index index = EMPTY;
    printf("    a b c d e f g h\n");
    printf("  o-----------------o\n");
    for (i = BOARD_DIM; i > 0; i--) {
        printf("%d |", i);
        for (j = 0; j < BOARD_DIM; j++) {
            index = game->board[BOARD_DIM - i][j];
            if (index == EMPTY || !is_alive(game->pieces[index])) {
                printf(" .");
                continue;
            }
            if (get_type(index) == PAWN && is_promoted(game->pieces[index])) {
                index = (get_color(index) == WHITE) ? MAX_QUEEN_INDEX - 1 : MAX_QUEEN_INDEX;
            }
            printf(" %c", get_piece_char(index));
        }
        printf(" | %d\n", i);
    }
    printf("  o-----------------o\n");
    printf("    a b c d e f g h\n");
}

int write_game_to_file(Game *game, char *file_name) {
    if (game == NULL || file_name == NULL) return -1;
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) return -1;
    Index index = 0;
    Piece piece = 0;
    for (index = 0; index < PIECES_NUM; index++) {
        piece = game->pieces[index];
        fprintf(fp, "%c %c %d %d\n",
            to_column_char(get_y(piece)),
            to_row_char(get_x(piece)),
            is_alive(piece),
            is_promoted(piece)
        );
    }
    fclose(fp);
    return 0;
}

int read_game_from_file(Game *game, char *file_name) {
    if (game == NULL || file_name == NULL) return -1;
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) return -1;
    empty_game(game);
    Index index = 0;
    Piece *piece = NULL;
    char string[9];
    for (index = 0; index < PIECES_NUM; index++) {
        if (fgets(string, 9, fp) == NULL) {
            fclose(fp);
            return -1;
        }
        piece = &(game->pieces[index]);
        if (!is_column_char(string[0])) return -1;
        set_y(piece, decode_column_char(string[0]));
        if (string[1] != ' ') return -1;
        if (!is_row_char(string[2])) return -1;
        set_x(piece, decode_row_char(string[2]));
        if (string[3] != ' ') return -1;
        if (string[4] != '0' && string[4] != '1') return -1;
        if (string[4] == '0') kill(piece);
        else revive(piece);
        if (string[5] != ' ') return -1;
        if (string[6] != '0' && string[6] != '1') return -1;
        if (string[6] == '0') depromote(piece);
        else promote(piece);
        if (string[7] != '\n') return -1;
        game->board[get_x(*piece)][get_y(*piece)] = index;
    }
    fclose(fp);
    return 0;
}