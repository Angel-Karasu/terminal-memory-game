#include <stdlib.h>

#include "cards.h"

const int nb_cards = 15;
char *card_pack[] = {"\
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

void shuffle_cards() {
    unsigned int nb_cards = sizeof(card_pack)/sizeof(card_pack[0]);

    for (unsigned int i=0; i<nb_cards; i++) {
        int r = rand() % nb_cards;
        char *temp = card_pack[r];
        card_pack[r] = card_pack[i];
        card_pack[i] = temp;
    }
}