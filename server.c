#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"
//#include "cards.h"


void process( char * s );
void sub_server( int sd );

int main() {

  int sd, connection;

  sd = server_setup();
    
  while (1) {

    connection = server_connect( sd );
    
    int f = fork();
    
    if ( f == 0 ) {
      
      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      close( connection );
    }
  }
  return 0;
}


void sub_server( int sd ) {
  

  char buffer[MESSAGE_BUFFER_SIZE];
  read(sd,buffer,sizeof(buffer));
  if (strcmp(buffer,"yes") == 0){
    printf("[SERVER] Player has joined!\n");
    update_playercount(1);
    //printf("[SERVER] Player count: %d\n", playercount);
  }
  while (read( sd, buffer, sizeof(buffer) )) {

    //printf("[SERVER %d] received: %s\n", getpid(), buffer );
    //process( buffer );
    write( sd, buffer, sizeof(buffer));    
  }
  
}
void process( char * s ) {

  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}
