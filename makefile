all: server client cards

server: server.o networking.o
	gcc -o server server.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

cards: cards.o 
	gcc -o cards cards.o
	
server.o: server.c networking.h
	gcc -c server.c

client.o: client.c networking.h
	gcc -c client.c
	
cards.o: cards.c cards.h
	gcc -c cards.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm client
	rm server
	rm cards

