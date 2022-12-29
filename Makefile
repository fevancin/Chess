ifeq ($(OS),Windows_NT)
	RM = del
	CHESS = chess.exe
else
	RM = rm
	CHESS = chess
endif

chess: obj/main.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o
	gcc -o chess obj/main.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o

clear:
	$(RM) obj/main.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o
	$(RM) $(CHESS)

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

obj/menu.o: src/menu.c src/menu.h
	gcc -c src/menu.c -o obj/menu.o

obj/search.o: src/search.c src/search.h
	gcc -c src/search.c -o obj/search.o

obj/value.o: src/value.c src/value.h
	gcc -c src/value.c -o obj/value.o

obj/bitboard.o: src/bitboard.c src/bitboard.h
	gcc -c src/bitboard.c -o obj/bitboard.o

obj/move.o: src/move.c src/move.h
	gcc -c src/move.c -o obj/move.o

obj/game.o: src/game.c src/game.h
	gcc -c src/game.c -o obj/game.o

obj/piece.o: src/piece.c src/piece.h
	gcc -c src/piece.c -o obj/piece.o

obj/utils.o: src/utils.c src/utils.h
	gcc -c src/utils.c -o obj/utils.o

obj/print_utils.o: src/print_utils.c src/print_utils.h
	gcc -c src/print_utils. -o obj/print_utils.oc