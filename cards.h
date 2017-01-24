#ifndef CARDS_H
#define CARDS_H

char *suits[4];
char num[13][15];
char deck[52][15];

void create_deck();

void print_deck();

char *get_card();


#endif
