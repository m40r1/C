/*basic things*/
#include <stdio.h>
#include <stdlib.h>
/*messing with the os*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/*structs and shit*/
#include <netinet/in.h>

int main() {

  int client_sock;
  client_sock = socket(AF_INET, SOCK_STREAM, 0); /*creating socket*/
  /*sets the connection config*/
  struct sockaddr_in server_address; /*struct for the address*/
  server_address.sin_family = AF_INET; /*gets the domain type*/
  server_address.sin_port = htons(9001); /*the port to connect*/
  server_address.sin_addr.s_addr = INADDR_ANY; /*the ip*/

  /*connect & check errs*/
  int conec_status =
      connect(client_sock, (struct sockaddr *)&server_address, sizeof(server_address));
  if (conec_status == -1){
    fprintf(stderr, "err to connect to the sock\n\n");
    exit(8);
  }
  
  char server_response[12];/*stores the response*/
  recv(client_sock, &server_response, sizeof(server_response), 0);/*gets the data and stores it*/
  fprintf(stdout, "server response %s\n", server_response);

  close(client_sock);/*close your socks*/
  return 0;
}


