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

void subserver_logic(int client_socket){
void* buf = calloc(256, sizeof(char));
int outcount;
outcount = recv(client_socket, buf, 256, 0);
printf("%s", buf);
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);
  if(fork()==0){
  subserver_logic(client_socket);
  }
}
