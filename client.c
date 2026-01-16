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

while (1){
  system("clear");
  printf("What should we call you? \n");
  fflush(stdout);
  fgets(usr, 63, stdin);
  int length = strlen(usr);
  if (length){
  *(usr+length-1)='\0';
  break;
}
  system("clear");
}
printf("Connected to Chat\n");
fflush(stdout);

      system("clear");
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
  if (!strcmp("!exit", msg)){
    err(bytes_sent = send(server_socket, "!exit", 5, 0),"49-client");
    free(fullmsg);
    free(msg);
    kill(pid, SIGQUIT);

          system("clear");
    break;
  }
  if (!strcmp("exit", msg)){
    strcat(fullmsg, "\033[;31mLEFT CHAT");
    strcat(fullmsg, "\033[m");
    len = strlen(fullmsg);
    *(fullmsg+len)='\0';
    err(bytes_sent = send(server_socket, fullmsg, len, 0), "62-client");
    free(fullmsg);
    free(msg);
    kill(pid, SIGQUIT);

      system("clear");
    break;
  }
strcat(fullmsg, msg);
strcat(fullmsg, "\033[m");
len = strlen(fullmsg);
*(fullmsg+len)='\0';
err(bytes_sent = send(server_socket, fullmsg, len, 0),"74-client");
}
}
}else{
  char* buf = (char*) calloc(256, sizeof(char));
  int outcount;
  while (1){
  err(outcount = recv(server_socket, buf, 1280, 0), "81-client");
  if(outcount){
    printf("%s\n", buf);
    fflush(stdout);
  }
  }
}
}

void sigquit_handler(int signum) {
    exit(0);
}


int main(int argc, char *argv[] ) {
      signal(SIGQUIT, sigquit_handler);
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  fflush(stdout);
  clientLogic(server_socket);
}
