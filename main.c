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
    int nb_rows;
    int nb_columns;
    int** board;
    couple* cards_found;
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
    int nb_rows, nb_columns, board_size;

    do {
        nb_rows = 1;
        printf("Choose number of rows ⟦1; %d⟧ : ", NB_CARDS/2);
        scanf("%d", &nb_rows);
    } while (nb_rows < 1 || nb_rows > NB_CARDS/2);

    do {
        nb_columns = 1;
        printf("Choose number of columns ⟦1;%d⟧ : ", NB_CARDS/nb_rows);
        scanf("%d", &nb_columns);
    } while (nb_columns < 1 || nb_columns > NB_CARDS/nb_rows);
    
    if (nb_rows%2 != 0 || nb_columns%2 != 0) {
        nb_columns++;
        printf("Number of columns increased by 1 for an even number of cards\n\n");
    }
    board_size = nb_columns*nb_rows;

    int** board = (int**)malloc(sizeof(int*)*nb_rows);
    int* values_cards = (int*)malloc(sizeof(int)*board_size);
    for (int i=0; i<board_size/2; i++) { values_cards[i*2]=i; values_cards[i*2+1]=i; }
    shuffle(values_cards, board_size);
    for (int i=0; i<nb_rows; i++) {
        board[i] = (int*)malloc(sizeof(int)*nb_columns);
        for (int j=0; j<nb_columns; j++) board[i][j] = values_cards[i*(nb_rows+1)+j];
    }
    free(values_cards);
    couple* cards_found = (couple*)malloc(sizeof(couple)*board_size);

    memory memory = {0, nb_rows, nb_columns, board, cards_found, 0};

    return memory;
}

bool card_is_found(int i, int j, couple* cards_found, int nb_cards_found) {
    for (int c=0; c<nb_cards_found; c++) if (i == cards_found[c].x && j == cards_found[c].y) return true;
    return false;
}

void show_memory(memory memory) {
    for (int i=0; i<memory.nb_rows; i++) {
        for (int j=0; j<memory.nb_columns; j++) printf("╶───╴");
        printf("\n");
        for (int j=0; j<memory.nb_columns; j++) {
            if (card_is_found(i, j, memory.cards_found, memory.nb_cards_found) == 1) printf("│XXX│");
            else printf("│%d,%d│", i, j);
        }
        printf("\n");
        for (int j=0; j<memory.nb_columns; j++) printf("╶───╴");
        printf("\n");
    }
}

void choose_card(memory* memory) {
    printf("Player %d must play\n", memory->actual_player);
    int i1, j1, i2, j2;

    do {
        i1 = 0;
        j1 = 0;
        printf("Choose 1st card (i,j) : ");
        scanf("%d,%d", &i1,&j1);
    } while (i1 < 0 || j1 < 0 || i1 >= memory->nb_rows || j1 >= memory->nb_columns || card_is_found(i1, j1, memory->cards_found, memory->nb_cards_found));

    int card1 = memory->board[i1][j1];
    printf("%s\n", cards[card1]);

    do {
        i2 = 0;
        j2 = 0;
        printf("Choose 2nd card (i,j) : ");
        scanf("%d,%d", &i2,&j2);
    } while (i2 < 0 || j2 < 0 || i2 >= memory->nb_rows || j2 >= memory->nb_columns || (i2 == i1 && j2 == j1) || card_is_found(i2, j2, memory->cards_found, memory->nb_cards_found));

    int card2 = memory->board[i2][j2];
    printf("%s\n", cards[card2]);

    if (card1 == card2) {
        player_scores[memory->actual_player]++;
        couple c1 = {i1,j1};
        memory->cards_found[memory->nb_cards_found] = c1;
        couple c2 = {i2,j2};
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

        while (memory.nb_cards_found < memory.nb_rows*memory.nb_columns) {
            show_memory(memory);
            choose_card(&memory);
            printf("\n");
        }
        printf("\nEnd of game !!!\n");

        best_player(memory);

        free(player_scores);
        for (int i=0; i<memory.nb_rows; i++) free(memory.board[i]);
        free(memory.board);

        printf("Play again ? (Y/N) : "); scanf(" %c", &play);
    }

   return 0;
}