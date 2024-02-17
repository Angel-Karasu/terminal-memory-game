#include <stdio.h>

#include "src/memory.h"

int main() {
    char is_playing = 'y';
    while (is_playing == 'y') {
        init_board();

        play();

        printf("\nEnd of game !!!\nPlay again ? (y/n) : "); scanf(" %c", &is_playing);
    }

   return 0;
}