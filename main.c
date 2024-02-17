#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

/* Change values to those desired */
#define NB_CARDS 15

char *cards[] = {"\
      /\\\n\
     /  \\\n\
    /`'.,\\\n\
   /     ',\n\
  /      ,`\\\n\
 /   ,.'`.  \\\n\
/.,'`     `'.\\",
"\
^__^\n\
(oo)\\_______\n\
(__)\\       )\\/\n\
    ||----w||\n\
    ||     ||",
"\
 .-.\n\
(o o) boo!\n\
| O \\\n\
 \\   \\\n\
  `~~~'",
"\
 _____\n\
|2    |\n\
|  v  |\n\
|  v  |\n\
|____Z|", "\
 _____\n\
|3    |\n\
| v v |\n\
|  v  |\n\
|____E|", "\
 _____\n\
|4    |\n\
| v v |\n\
| v v |\n\
|____h|", "\
 _____\n\
|2    |\n\
|  o  |\n\
|  o  |\n\
|____Z|", "\
 _____\n\
|3    |\n\
| o o |\n\
|  o  |\n\
|____E|", "\
 _____\n\
|4    |\n\
| o o |\n\
| o o |\n\
|____h|", "\
 _____\n\
|2    |\n\
|  &  |\n\
|  &  |\n\
|____Z|", "\
 _____\n\
|3    |\n\
| & & |\n\
|  &  |\n\
|____E|", "\
 _____\n\
|4    |\n\
| & & |\n\
| & & |\n\
|____h|", "\
 _____\n\
|2    |\n\
|  ^  |\n\
|  ^  |\n\
|____Z|", "\
 _____\n\
|3    |\n\
| ^ ^ |\n\
|  ^  |\n\
|____E|", "\
 _____\n\
|4    |\n\
| ^ ^ |\n\
| ^ ^ |\n\
|____h|"
};
/* */

typedef struct { int x, y; } couple;

typedef struct {
    int actual_player;
    int nb_cards;
    int *board;
    int *cards_found;
    int nb_cards_found;
} memory;

int nb_players;
int *player_scores;
void init_players() {
    do {
        nb_players = 1;
        printf("Choose number of players : ");
        scanf("%d", &nb_players);
    } while (nb_players < 1);

    player_scores = (int *)malloc(sizeof(int)*nb_players);
    for (int i=0; i<nb_players; i++) player_scores[i] = 0;
}

void shuffle_cards() {
    srand(time(NULL));

    for (int i=0; i<NB_CARDS; i++) {
        int r = rand() % NB_CARDS;
        char *temp = cards[r];
        cards[r] = cards[i];
        cards[i] = temp;
    }
}

void shuffle(int* list, int length) {
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        int r = rand() % length;
        int temp = list[r];
        list[r] = list[i];
        list[i] = temp;
    }
}

memory generate_memory() {
    int nb_cards;
    do {
        nb_cards = 1;
        printf("Choose the number of different cards in the game ⟦1; %d⟧ : ", NB_CARDS);
        scanf("%d", &nb_cards);
    } while (nb_cards < 1 || nb_cards > NB_CARDS);
    nb_cards *= 2;

    int* board = (int*)malloc(sizeof(int)*nb_cards);
    for (int i=0; i<nb_cards/2; i++) {
        board[i*2] = i;
        board[i*2+1] = i;
    }
    shuffle(board, nb_cards);
    int *cards_found = (int*)malloc(sizeof(int)*nb_cards);

    memory memory = {0, nb_cards, board, cards_found, 0};

    return memory;
}

bool card_is_found(int c, int *cards_found, int nb_cards_found) {
    for (int i=0; i<nb_cards_found; i++) if (c == cards_found[i]) return true;
    return false;
}

void show_memory(memory memory) {
    for (int i=0; i<memory.nb_cards; i++) {
        if (card_is_found(i, memory.cards_found, memory.nb_cards_found)) printf("│XXX│");
        else printf("│%d│", i);
        printf("\n");
    }
}

void choose_card(memory* memory) {
    printf("Player %d must play\n", memory->actual_player);
    int c1, c2;

    do {
        c1 = 0;
        printf("Choose 1st card : ");
        scanf("%d", &c1);
    } while (c1 < 0 || c1 > memory->nb_cards || card_is_found(c1, memory->cards_found, memory->nb_cards_found));

    int card1 = memory->board[c1];
    printf("%s\n", cards[card1]);

    do {
        c2 = 0;
        printf("Choose 2nd card : ");
        scanf("%d", &c2);
    } while (c2 < 0 || c2 > memory->nb_cards || c2 == c1 || card_is_found(c2, memory->cards_found, memory->nb_cards_found));

    int card2 = memory->board[c2];
    printf("%s\n", cards[card2]);

    if (card1 == card2) {
        player_scores[memory->actual_player]++;
        memory->cards_found[memory->nb_cards_found] = c1;
        memory->cards_found[memory->nb_cards_found+1] = c2;
        memory->nb_cards_found += 2;
        printf("You found a pair\n");
    } else {
        memory->actual_player = (memory->actual_player+1)%nb_players;
        printf("You didn't find a pair\n");
    }
}

void best_player() {
    int i_best_player = 0;
    int score_best_player = player_scores[i_best_player];
    for (int i=1; i<nb_players; i++) {
        if (player_scores[i] > score_best_player) {
            score_best_player = player_scores[i];
            i_best_player = i;
        }
    }
    printf("The best player is the player %d with %d points !!!\n", i_best_player, score_best_player);
}

int main() {
    char play = 'Y';
    while (play == 'Y') {
        shuffle_cards();
        init_players();
        memory memory = generate_memory();

        while (memory.nb_cards_found < memory.nb_cards) {
            show_memory(memory);
            choose_card(&memory);
            printf("\n");
        }
        printf("\nEnd of game !!!\n");

        best_player(memory);

        free(player_scores);
        free(memory.board);

        printf("Play again ? (Y/N) : "); scanf(" %c", &play);
    }

   return 0;
}