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
char *usr = (char*) calloc(64, sizeof(char));
printf("What should we call you? \n");
while (1){
  fgets(usr, 63, stdin);
  int length = strlen(usr);
  if (length){
  *(usr+length-1)='\0';
  break;
}
}
printf("Connected to Chat\n");

while (1){
int len, bytes_sent;
fgets(msg, 1023, stdin);

len = strlen(msg);
*(msg+len-1)='\0';
char *fullmsg = (char*) calloc(1280,sizeof (char));
strcpy(fullmsg, "\033[;34m");
strcat(fullmsg, usr);
strcat(fullmsg, "\033[m: \033[;93m");

if (len){
strcat(fullmsg, msg);
strcat(fullmsg, "\033[m");
len = strlen(fullmsg);
*(fullmsg+len-1)='\0';
bytes_sent = send(server_socket, fullmsg, len, 0);
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
