#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "blackjack.h"
/*
-----------------------------------------------------------------------------------------------------------------------------
globals
-----------------------------------------------------------------------------------------------------------------------------
*/
int deck[52];
int deck_pos;
int n_players;
char* name[9];
int bal[9];
int hand[9][6];
int hand_pos[9];
int hand_tot_min[9];
int hand_tot_max[9];
int curr_player;
bool active[9];
int bet[9];
int n_bets;
bool blackjack[9];
bool busted[9];
bool complete[9];
/*
-----------------------------------------------------------------------------------------------------------------------------
main
-----------------------------------------------------------------------------------------------------------------------------
*/
/*
int main()
{
	init_game();
	for (;;) {
		init_round();
		if (no_bets()) break;
		play_round();
		if (! another_round()) break;
	}
	return 0;
}
*/
/*
-----------------------------------------------------------------------------------------------------------------------------
init_game
-----------------------------------------------------------------------------------------------------------------------------
*/
void init_game()
{
	int i;
	
	for (i=0;i<52;++i) deck[i]=i;
	get_players();
	srand(time(NULL));
}
/*
-----------------------------------------------------------------------------------------------------------------------------
init_round
-----------------------------------------------------------------------------------------------------------------------------
*/
void init_round()
{
	get_bets();
	init_hands();
}
/*
-----------------------------------------------------------------------------------------------------------------------------
no_bets
-----------------------------------------------------------------------------------------------------------------------------
*/
bool no_bets()
{
	return (n_bets==0);
}
/*
-----------------------------------------------------------------------------------------------------------------------------
play_round
-----------------------------------------------------------------------------------------------------------------------------
*/
void play_round()
{
	int p;
	
	shuffle();
	deal_initial_cards();
	check_blackjacks();
	//for (p=1;p<=n_players;++p) play_hand_player(p);
	//play_hand_dealer();
}
/*
-----------------------------------------------------------------------------------------------------------------------------
another_round
-----------------------------------------------------------------------------------------------------------------------------
*/
bool another_round()
{
	int p;
	
	for (p=1;p<=n_players;++p) {
		if (active[p]) return true;
	}
	return false;
}
/*
-----------------------------------------------------------------------------------------------------------------------------
get_players
-----------------------------------------------------------------------------------------------------------------------------
*/
void get_players()
{
	int p;
	
	n_players=3;
	for (p=0;p<=n_players;++p) {
		active[p]=true;
		bal[p]=0;
		name[p]=malloc(32);
		if (p==0) 
			strcpy(name[p],"Dealer");
		else
			sprintf(name[p],"Player %d",p);
	}
}
/*
-----------------------------------------------------------------------------------------------------------------------------
get_bets
-----------------------------------------------------------------------------------------------------------------------------
*/
void get_bets()
{
	int p;
	
	for (p=1;p<=n_players;++p) {
		active[p]=true;
		bet[p]=1;
		
	}
	n_bets=n_players;
}
/*
-----------------------------------------------------------------------------------------------------------------------------
shuffle
-----------------------------------------------------------------------------------------------------------------------------
*/
void shuffle()
{
	int i,r,v,w;
	
	for (i=0;i<52;++i) {
		r=rand() % 52;
		v=deck[i];
		if (r!=i) {
			w=deck[r];
			deck[r]=v;
			deck[i]=w;
		}
	}
	deck_pos=0;
}
/*
-----------------------------------------------------------------------------------------------------------------------------
init_hands
-----------------------------------------------------------------------------------------------------------------------------
*/
void init_hands()
{
	int p;
	
	for (p=1;p<=n_players;++p) {
		if (bet[p]>0) {
			hand_pos[p]=0;
			hand_tot_min[p]=0;
			hand_tot_max[p]=0;
		}
	}
}
/*
-----------------------------------------------------------------------------------------------------------------------------
deal_initial_cards
-----------------------------------------------------------------------------------------------------------------------------
*/
void deal_initial_cards()
{
	int i,q,p,v;
	
	for (q=1;q<=n_players+1;++q) {
		if (q<=n_players) p=q; else p=0;
		if ((p>0)&&(bet[p]==0)) continue;
		for (i=0;i<=1;++i) {
			v=deck[deck_pos++];
			hand[p][i]=v;
			update_tots(v,p);
		}
		hand_pos[p]=2;
	}
	show_table();
}
/*
-----------------------------------------------------------------------------------------------------------------------------
update_tots
-----------------------------------------------------------------------------------------------------------------------------
*/
void update_tots(int v,int p)
{
	int r;
	
	r=(v%13)+1;
	if (r>=10) r=10; 
	if (r==1) {
		hand_tot_min[p]+=1;
		hand_tot_max[p]+=11;}
	else {
		hand_tot_min[p]+=r;
		hand_tot_max[p]+=r;
	}
}
/*
-----------------------------------------------------------------------------------------------------------------------------
check_blackjacks()
-----------------------------------------------------------------------------------------------------------------------------
*/
void	check_blackjacks()
{
	int p,x,y,z;
	
	for (p=0;p<=n_players;++p) {
		blackjack[p]=false;
		if ((p>0)&&(bet[p]==0)) continue;
		x=((hand[p][0])%13)+1;
		y=((hand[p][1])%13)+1;
		z=x;
		if (x>y) {x=y; y=z;}
		if ((x==1)&&(y>=10)) blackjack[p]=true;	
	}
}
/*
-----------------------------------------------------------------------------------------------------------------------------
show_table
-----------------------------------------------------------------------------------------------------------------------------
*/
void show_table()
{
	int p,i,c,v,s;
	char* v_name="A23456789TJQK";
	char* s_name="SHDC";
	
	printf("name bal bet hand status\n");
	printf("---- --- --- ---- ------\n");
	for (p=0;p<=n_players;++p) {
		printf("%s %d %d",name[p],bal[p],bet[p]);
		for (i=0;i<hand_pos[p];i++) {
			c=hand[p][i];
			v=c%13;
			s=c/13;
			printf(" %c%c",v_name[v],s_name[s]);
		}
		if (!active[p]) 
			printf("quit");
		else if (bet[p]==0)
			printf("no bet");
		else if (blackjack[p])
			printf("blackjack");
		else if (busted[p])
			printf("busted");
		else if (complete[p])
			printf("completed");
		else
			printf("in progress");
		printf("\n");
	}
	sleep(10);
}
/*
-----------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------------------------------------------------------------
*/
