.PHONY: clean run

compile: client.o mainServer.o
		@gcc -o client client.o
		@gcc -o mainServer mainServer.o

client.o: client.c
				@gcc -c client.c

clean:
	@rm *.o
	@rm mainServer
	@rm client
