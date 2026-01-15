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
//static void sighandler(int signo){
//
//}


void subserver_logic(int client_socket){
char* buf = (char*) calloc(256, sizeof(char));
int outcount, incount;
while (1){
outcount = recv(client_socket, buf, 255, 0);
if(!strcmp("exit", buf)){
printf("exiting");
break;
}
if(outcount){
  printf("%s\n", buf);
  incount = send(client_socket, buf, outcount, 0);
}
}
}

int main(int argc, char *argv[] ) {
//  while (1){
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);
  if(fork()==0){
  subserver_logic(client_socket);
  }

//}
}
