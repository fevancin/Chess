ifeq ($(OS),Windows_NT) # differences in Windows systems
	RM = del
	CHESS = chess.exe
	TEST = test.exe
else
	RM = rm
	CHESS = chess
	TEST = test
endif

chess: obj/main.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o
	gcc -o chess obj/main.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o

test: obj/tests.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o
	gcc -o test obj/tests.o obj/menu.o obj/search.o obj/value.o obj/bitboard.o obj/move.o obj/game.o obj/piece.o obj/utils.o

clear:
	$(RM) obj\tests.o
	$(RM) obj\main.o
	$(RM) obj\menu.o
	$(RM) obj\search.o
	$(RM) obj\value.o
	$(RM) obj\bitboard.o
	$(RM) obj\move.o
	$(RM) obj\game.o
	$(RM) obj\piece.o
	$(RM) obj\utils.o
	$(RM) $(CHESS)
	$(RM) $(TEST)

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

obj/menu.o: src/menu.c src/header/menu.h
	gcc -c src/menu.c -o obj/menu.o

obj/search.o: src/search.c src/header/search.h
	gcc -c src/search.c -o obj/search.o

obj/value.o: src/value.c src/header/value.h
	gcc -c src/value.c -o obj/value.o

obj/bitboard.o: src/bitboard.c src/header/bitboard.h
	gcc -c src/bitboard.c -o obj/bitboard.o

obj/move.o: src/move.c src/header/move.h
	gcc -c src/move.c -o obj/move.o

obj/game.o: src/game.c src/header/game.h
	gcc -c src/game.c -o obj/game.o

obj/piece.o: src/piece.c src/header/piece.h
	gcc -c src/piece.c -o obj/piece.o

obj/utils.o: src/utils.c src/header/utils.h
	gcc -c src/utils.c -o obj/utils.o

obj/tests.o: src/tests.c
	gcc -c src/tests.c -o obj/tests.o

obj/print_utils.o: src/print_utils.c src/header/print_utils.h
	gcc -c src/print_utils. -o obj/print_utils.oc