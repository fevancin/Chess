#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint8_t Coordinate;
#define BOARD_DIM (Coordinate)8

// true if coordinate is in range 0..(BOARD_DIM - 1)
int is_valid_coordinate(Coordinate coordinate);

typedef uint8_t Color;
#define WHITE ((Color)0)
#define BLACK ((Color)1)

// returns BLACK if WHITE and viceversa
Color swap_color(Color color);

// pieces are mapped into fixed numbers:
// 0, 1 = KINGS
// 2, 3 = QUEENS
// 4, 5, 6, 7 = ROOKS
// 8, 9, 10, 11 = KNIGHTS
// 12, 13, 14, 15 = BISHOPS
// 16 to 31 = PAWNS
typedef uint8_t Index;
#define PIECES_NUM ((Index)32)
#define MAX_KING_INDEX ((Index)1)
#define MAX_QUEEN_INDEX ((Index)3)
#define MAX_ROOK_INDEX ((Index)7)
#define MAX_KNIGHT_INDEX ((Index)11)
#define MAX_BISHOP_INDEX ((Index)15)
#define MAX_PAWN_INDEX ((Index)31)
#define EMPTY ((Index)32)

// type of pieces, plus UNKNOWN
typedef uint8_t Type;
#define KING ((Type)0)
#define QUEEN ((Type)1)
#define ROOK ((Type)2)
#define KNIGHT ((Type)3)
#define BISHOP ((Type)4)
#define PAWN ((Type)5)
#define UNKNOWN ((Type)6)

// map index to piece type
Type get_type(Index index);

// return color of the index (even is WHITE, odd is BLACK)
Color get_color(Index index);

// translate from index to char (e.g. 2 to 'Q')
char get_piece_char(Index index);