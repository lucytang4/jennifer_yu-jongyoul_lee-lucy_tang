all: server client 

server: server.o networking.o cards.o
	gcc -o server server.o networking.o cards.o

client: client.o networking.o cards.o
	gcc -o client client.o networking.o cards.o
	
server.o: server.c networking.h cards.h
	gcc -c server.c

client.o: client.c networking.h cards.h
	gcc -c client.c
	
cards.o: cards.c cards.h
	gcc -c cards.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm client
	rm server

