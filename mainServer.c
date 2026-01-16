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

void sigquit_handler(int signum) {
    exit(0);
}

void reader_logic(int listen_socket, int client_socket, fd_set* fds, int max){
fd_set read_fds = *fds;
char* buf = (char*) calloc(1281, sizeof(char));
int outcount, incount;
err(outcount = recv(client_socket, buf, 1280, 0),"24-mainServer");
if(!strcmp("!exit", buf)){
printf("exiting\n");
exit(0);
}

    if (outcount <= 0) {
        close(client_socket);
        FD_CLR(client_socket, fds);
        return;
    }

if(outcount){
  printf("%s\n", buf);
  fflush(stdout);
  for (int i = 0; i< max; i++){
    if (FD_ISSET(i, &read_fds) && i!=client_socket && i!=listen_socket){
  (incount = send(i, buf, outcount+1, 0), "41-mainServer");
}
}
}
if (strstr(buf, "\033[;31mLEFT CHAT")) {
    printf("Client Left\n");
    close(client_socket);
    FD_CLR(client_socket, fds);
}
free(buf);
}


int main(int argc, char *argv[] ) {
      signal(SIGQUIT, sigquit_handler);
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
      reader_logic(listen_socket, i, &read_fds, max_descriptor+1);
    }
  }
}
}

}
