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
int outcount;
while (1){
outcount = recv(client_socket, buf, 255, 0);
printf("help me, obi wan %d\n", outcount);
printf("%s\n", buf);
}
}

int main(int argc, char *argv[] ) {
//  while (1){
  printf("haaalp\n");
  int listen_socket = server_setup();
  printf("line 25\n");


  int client_socket = server_tcp_handshake(listen_socket);
  printf("handshook\n");
  if(fork()==0){
  subserver_logic(client_socket);
  }
//}
}
