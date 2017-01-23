#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//char *suits[4] = {"Diamond","Club","Heart","Spade"};
//char num[13][15] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
//char deck[52][15];

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

/*void shuffle_deck(){
    int i;
    for (i=0;i<52;i++){
        char *a=deck[i];
        ran = srand(time(NULL)) % 52;
        char *b=deck[ran];
        deck[i]=&b;
        deck[ran]=&a;
    }
}*/

char *get_card(){
    srand(time(NULL));
    int i = rand()%52;
    char *card = deck[i];
    return card;
}
/*
int get_value(char *card) {
    if (card)
    strchr(card, " ");
}*/


int main()
{
	/*shuffle();
	for (;;) {
		for (;;) {
			getNumPlayers();
			if (nplayers==0) break;
			takeBets();
			initialDeal();
			if (dealerBlackjack()) {collectBets(); break;}
			
		}
		if (ncardsLeft<52) shuffle();
}*/
    create_deck();
    print_deck();
    char *card = get_card();
    printf("random card: %s\n", card);


//deal two cards to each player, including dealer, dealer's first card down

    return 0;
}
