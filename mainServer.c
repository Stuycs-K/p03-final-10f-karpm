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
exit(0);
}
if(outcount){
  printf("%s\n", buf);
  incount = send(client_socket, buf, outcount, 0);
}
}
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(listen_socket, &read_fds);
  int max_descriptor = listen_socket;

while(1){
  fd_set temp_fds;
  FD_ZERO(&temp_fds);
  temp_fds = read_fds;
  int state = select(max_descriptor+1, &temp_fds, NULL, NULL, NULL);
  if (FD_ISSET(listen_socket, &temp_fds)){
  int client_socket = server_tcp_handshake(listen_socket);
  if (client_socket>max_descriptor){
    max_descriptor = client_socket;
  }
  FD_SET(client_socket, &read_fds);
}else{
  for (int i = 0; i<= max_descriptor; i++){
    if (FD_ISSET(i, &temp_fds)){
      subserver_logic(i);
    }
  }
}
}

}
