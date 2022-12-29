#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint8_t Coordinate;
#define BOARD_DIM (Coordinate)8

int is_valid_coordinate(Coordinate coordinate);

typedef uint8_t Color;
#define WHITE ((Color)0)
#define BLACK ((Color)1)

Color swap_color(Color color);

typedef uint8_t Index;
#define PIECES_NUM 32
#define MAX_KING_INDEX ((Index)1)
#define MAX_QUEEN_INDEX ((Index)3)
#define MAX_ROOK_INDEX ((Index)7)
#define MAX_KNIGHT_INDEX ((Index)11)
#define MAX_BISHOP_INDEX ((Index)15)
#define MAX_PAWN_INDEX ((Index)31)
#define EMPTY ((Index)32)

char get_piece_char(Index index);

typedef uint8_t Type;
#define KING ((Type)0)
#define QUEEN ((Type)1)
#define ROOK ((Type)2)
#define KNIGHT ((Type)3)
#define BISHOP ((Type)4)
#define PAWN ((Type)5)
#define UNKNOWN ((Type)6)

Type get_type(Index index);

Color get_color(Index index);