#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "networking.h"

void clientLogic(int server_socket){
char *msg = (char*) calloc(1024, sizeof(char));
fgets(msg, 1023, stdin);
int len, bytes_sent;

len = strlen(msg);
printf("%d",len);
bytes_sent = send(server_socket, msg, len, 0);
send(server_socket, "exit", 4, 0);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
