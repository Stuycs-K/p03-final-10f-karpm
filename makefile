.PHONY: clean

compile: client.o mainServer.o networking.o
	@gcc -o client client.o networking.o
	@gcc -o mainServer mainServer.o networking.o

client: client
	@./client

server: mainServer
	@./mainServer

client.o: client.c networking.h
	@gcc -c client.c

mainServer.o: mainServer.c networking.h
	@gcc -c mainServer.c

networking.o: networking.c networking.h
	@gcc -c networking.c

clean:
	@rm *.o
	@rm mainServer
	@rm client
