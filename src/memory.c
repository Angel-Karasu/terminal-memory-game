#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cards.h"
#include "players.h"

typedef struct {
    int actual_player;
    int nb_cards;
    int *cards;
    bool *cards_found;
    int nb_cards_found;
} memory;

memory board;

void init_board() {
    srand(time(NULL));

    /* Shuffle the deck of cards */
    for (int i=0; i<nb_cards; i++) {
        int r = rand() % nb_cards;
        char *temp = card_pack[r];
        card_pack[r] = card_pack[i];
        card_pack[i] = temp;
    }
    /* */

    init_players();
    board.actual_player = 0;

    do {
        board.nb_cards = 1;
        printf("Choose the number of different cards in the game ⟦2; %d⟧ : ", nb_cards);
        scanf("%d", &(board.nb_cards));
    } while (board.nb_cards < 2 || board.nb_cards > nb_cards);
    board.nb_cards *= 2;

    board.cards = (int*)malloc(sizeof(int)*board.nb_cards);
    for (int i=0; i<board.nb_cards/2; i++) {
        board.cards[i*2] = i;
        board.cards[i*2+1] = i;
    }

    /* Shuffle cards on the board */
    for (int i=0; i<nb_cards; i++) {
        int r = rand() % nb_cards;
        char *temp = card_pack[r];
        card_pack[r] = card_pack[i];
        card_pack[i] = temp;
    }
    /* */

    board.cards_found = (bool*)malloc(sizeof(bool)*board.nb_cards);
    for (int i=0; i<board.nb_cards; i++) board.cards_found[i] = false;
    board.nb_cards_found = 0;
}

void choose_card() {
    int c1, c2;

    do {
        c1 = 0;
        printf("Choose 1st card : ");
        scanf("%d", &c1);
    } while (c1 < 0 || c1 > board.nb_cards || board.cards_found[c1]);

    int card1 = board.cards[c1];
    printf("%s\n", card_pack[card1]);

    do {
        c2 = 0;
        printf("Choose 2nd card : ");
        scanf("%d", &c2);
    } while (c2 < 0 || c2 > board.nb_cards || c2 == c1 || board.cards_found[c2]);

    int card2 = board.cards[c2];
    printf("%s\n\n", card_pack[card2]);

    if (card1 == card2) {
        player_scores[board.actual_player]++;
        board.cards_found[c1] = board.cards_found[c2] = true;
        board.nb_cards_found += 2;
        printf("You found a pair");
    } else {
        board.actual_player = (board.actual_player+1) % nb_players;
        printf("You didn't find a pair");
    }
}

void show_board() {
    printf("╶───╴\n");
    for (int i=0; i<board.nb_cards; i++) {
        if (board.cards_found[i]) printf("│X");
        else printf("│%d", i);
        if (i%2 == 1) printf("│\n╶───╴\n");
    }
}

void play() {
    while (board.nb_cards_found < board.nb_cards) {
        show_board();
        printf("Player %d must play\n", board.actual_player+1);
        choose_card();
        printf("\n\n");
    }

    show_best_player();

    free(board.cards);
    free(board.cards_found);
}