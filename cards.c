#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cards.h"

int deck_pos;
char *suits[4] = {"Diamond","Club","Heart","Spade"};
char num[13][15] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char deck[52][15];

void create_deck(){
    int suitCtr, numCtr, deckCtr;
    for (numCtr = 0; numCtr < 13; numCtr++){
        for (suitCtr = 0; suitCtr < 4; suitCtr++){
            char tmp[15];
            strcpy(tmp,num[numCtr]);
            strcat(tmp," ");
            strcat(tmp,suits[suitCtr]);
            //printf("1ststrcat: %s\n", tmp);
            strcat(deck[deckCtr],tmp);
            deckCtr++;
        }
    }
    
}

void print_deck(){
    int x = 0;
    printf("DECK: \n");
    for (; x < 52; x++){
        printf("%s\n", deck[x]);
    }
}

char *get_card(){
    srand(time(NULL));
    int i = rand()%52;
    char *card = deck[i];
    return card;
}


void shuffle_deck(){
    int i,ran;
    for (i=0;i<52;i++){
        char *a=deck[i];
        srand(time(NULL));
        ran = rand()%52;
        char *b=deck[ran];
        //swap_cards(a,b,i,ran);
        memcpy(deck[i],b,sizeof(deck[i]));
        memcpy(deck[ran],a,sizeof(deck[ran]));
    }
}

/*void swap_cards(char *card1, char *card2, int i, int ran){
    memcpy(deck[i],card2,sizeof(deck[i]));
        memcpy(deck[ran],card1,sizeof(deck[ran]));
}*/




int get_value(char *card) {
    if (card[0] == 'A')
        return 1; //for now lets just make it 1
    else if(card[0] == '1' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') //for 10, J, Q, K
        return 10;
    else
        return card[0] - '0';
}


/*int main()
{
	shuffle();
	for (;;) {
		for (;;) {
			getNumPlayers();
			if (nplayers==0) break;
			takeBets();
			initialDeal();
			if (dealerBlackjack()) {collectBets(); break;}
			
		}
		if (ncardsLeft<52) shuffle();
}
    create_deck();
    print_deck();
    char *card = get_card();
    printf("random card: %s\n", card);
    printf("card value: %d\n", get_value(card));
    shuffle_deck();
    print_deck();


//deal two cards to each player, including dealer, dealer's first card down

    return 0;
}*/
