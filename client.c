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
int pid = fork();
if (!pid){
char *msg = (char*) calloc(1024, sizeof(char));
while (1){
int len, bytes_sent;
fgets(msg, 1023, stdin);

len = strlen(msg);
*(msg+len-1)='\0';
if (len){
bytes_sent = send(server_socket, msg, len, 0);
}
if (!strcmp("exit", msg)){
  kill(pid, SIGQUIT);
  break;
}
}
}else{
  char* buf = (char*) calloc(256, sizeof(char));
  int outcount;
  while (1){
  outcount = recv(server_socket, buf, 255, 0);
  if(outcount){
    printf("%s\n", buf);
  }
  }
}
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
