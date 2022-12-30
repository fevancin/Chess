#include "header/menu.h"

int main(int argc, char *argv[]) {
    Game game;
    play_menu(&game);
    clear_console();
    play_game(&game);
    exit(0);
}