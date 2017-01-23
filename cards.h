#ifndef CARDS_H
#define CARDS_H

char *suits[4] = {"Diamond","Club","Heart","Spade"};
char num[13][15] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char deck[52][15];

void create_deck();

void print_deck();

char *get_card();


#endif
