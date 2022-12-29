ifeq ($(OS),Windows_NT)
	RM = del
	CHESS = chess.exe
else
	RM = rm
	CHESS = chess
endif

chess: main.o menu.o search.o value.o bitboard.o move.o game.o piece.o utils.o
	gcc -o chess main.o menu.o search.o value.o bitboard.o move.o game.o piece.o utils.o

clear:
	$(RM) main.o menu.o search.o value.o bitboard.o move.o game.o piece.o utils.o
	$(RM) $(CHESS)

main.o: main.c
	gcc -c main.c

menu.o: menu.c menu.h
	gcc -c menu.c

search.o: search.c search.h
	gcc -c search.c

value.o: value.c value.h
	gcc -c value.c

bitboard.o: bitboard.c bitboard.h
	gcc -c bitboard.c

move.o: move.c move.h
	gcc -c move.c

game.o: game.c game.h
	gcc -c game.c

piece.o: piece.c piece.h
	gcc -c piece.c

utils.o: utils.c utils.h
	gcc -c utils.c

print_utils.o: print_utils.c print_utils.h
	gcc -c print_utils.c