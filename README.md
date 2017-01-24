# jennifer_yu-jongyoul_lee-lucy_tang

Jennifer Yu Pd 4
Jongyoul Lee Pd 4
Lucy Tang Pd 4

Files that should be in repo:
________________
blackjack.c

blackjack.h

client.c

makefile

networking.c

networking.h

server.c

DESIGN.txt

DEVOG.txt

README.md
________________

To run:
"make clean"
"make"
"./server" in one terminal
"./client" in another

Upon running client, user will be asked to join game. Game will start when user responds "yes."
At each turn, the player will be asked if they want to "hit" or "pass."

One player functionality, can be tested locally.
The server can be left alone, the client is you.
Did not complete networking aspect.

If you and the dealer get a blackjack, you win. :))

BUGS

Ace is counted as 1 for simplicity.  
When receiving a new card, you get 10 instead of J, Q, K  
Betting and balance is not implemented.  
Player only takes one turn. (Ran out of time to put a while loop)  
When the dealer gets a 20, it doesn't print the "Dealer does not take a card. Your Turn!" message

Please note that we worked in cloud9 for the majority of the project for optimal
collaboration. Hence why our commits are directly from Lucy.
Check DEVLOG for accurate division of parts.
