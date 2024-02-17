#include <stdio.h>

#include "src/memory.h"

int main() {
    char is_playing = 'y';
    while (is_playing == 'y') {
        init_board();

        play();
        printf("\nEnd of game !!!\n");

        // show_best_player();

        // free(memory.board);
        // free(memory.cards_found);

        printf("Play again ? (y/n) : "); scanf(" %c", &is_playing);
    }

   return 0;
}