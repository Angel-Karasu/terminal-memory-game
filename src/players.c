#include <stdlib.h>

int nb_players, *player_scores;
void init_players() {
    do {
        nb_players = 1;
        printf("Choose number of players : ");
        scanf("%d", &nb_players);
    } while (nb_players < 1);

    player_scores = (int *)malloc(sizeof(int)*nb_players);
    for (int i=0; i<nb_players; i++) player_scores[i] = 0;
}

void show_best_player() {
    int i_best_player, score_best_player = 0;
    for (int i=0; i<nb_players; i++) if (player_scores[i] > score_best_player) {
        score_best_player = player_scores[i];
        i_best_player = i;
    }
    printf("The best player is the player %d with %d points !!!\n", i_best_player+1, score_best_player);

    free(player_scores);
}