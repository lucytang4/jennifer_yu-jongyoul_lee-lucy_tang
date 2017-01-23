#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "networking.h"
#include "cards.h"

int main( int argc, char *argv[] ) {

  char *host;
  if (argc != 2 ) {
    printf("host not specified, connecting to 127.0.0.1\n");
    host = "127.0.0.1";
  }
  else
    host = argv[1];
  
  int sd;

  sd = client_connect( host );

  char buffer[MESSAGE_BUFFER_SIZE];
  char *tmp = buffer;
  
  printf("You are now playing BLACKJACK!\n");
  printf("Would you like to join the table? Enter yes or no.\n");
  fgets(buffer,sizeof(buffer),stdin);

  //printf("buffer BEFORE: <%s>\n", tmp);
  while (*tmp != '\n'){
    //printf("*tmp BEFORE: %c\n", *tmp);
    *tmp = tolower(*tmp);
    //printf("*tmp AFTER: %c\n", *tmp);
    tmp++;
  }
  char *p = strchr(buffer,'\n');
  *p = 0;
  //printf("buffer AFTER: <%s>\n", buffer);
  
  while (!(strcmp("yes",buffer) == 0 | strcmp("no",buffer) == 0)){
    printf("You haven't correctly entered yes or no.\n");
    printf("Would you like to join the table? Enter yes or no.\n");
    fgets(buffer,sizeof(buffer),stdin);
    tmp = buffer;
    //printf("buffer BEFORE: <%s>\n", tmp);
    while (*tmp != '\n'){
      //printf("*tmp BEFORE: %c\n", *tmp);
      *tmp = tolower(*tmp);
      //printf("*tmp AFTER: %c\n", *tmp);
      tmp++;
    }
    char *p = strchr(buffer,'\n');
    *p = 0;
    //printf("buffer AFTER: <%s>\n", buffer);
  }
  if (strcmp("yes",buffer) == 0){
    printf("You have joined!\n");
    write(sd,buffer,sizeof(buffer));
    char *card1 = get_card();
    char *card2 = get_card();
    int value1 = get_value(card1);
    int value2 = get_value(card2);
    int total = value1 + value2;
    printf("Your first two cards have been dealt:\n%s\n%s\n", card1, card2);
    
/*
    //INSTANT BLACKJACK
    if (total == 21) {
      printf("Wow, you have a blackjack already!");
    }
*/

    while ( total < 21 & (!(strcmp("pass",buffer) == 0))) {
      
      printf("What would you like to do? Enter hit or pass.\n");

      fgets(buffer,sizeof(buffer),stdin);
      tmp = buffer;
      while (*tmp != '\n'){
        *tmp = tolower(*tmp);
        tmp++;
      }
      char *p = strchr(buffer,'\n');
      *p = 0;
      
      while (!(strcmp("hit",buffer) == 0 | strcmp("pass",buffer) == 0)){
        printf("You haven't correctly entered hit or pass.\n");
        fgets(buffer,sizeof(buffer),stdin);
        tmp = buffer;
        while (*tmp != '\n'){
          *tmp = tolower(*tmp);
          tmp++;
        }
        char *p = strchr(buffer,'\n');
        *p = 0;
      }
    
      if (strcmp("hit",buffer) == 0){
        char * newcard = get_card();
        int newcardvalue = get_value(newcard);
        total += newcardvalue;
      }
    }

  }
  else if (strcmp("no",buffer) == 0){
    exit(0);
  }
  
  /*while (1) {
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    p = strchr(buffer, '\n');
    *p = 0;
  
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
  }*/
  
  return 0;
}
