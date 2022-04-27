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

  char serv_msg[12] = "Hello world";/*its a polite server*/

  int serv_sock;
  serv_sock = socket(AF_INET, SOCK_STREAM, 0); /*creating socket*/

  /*setting the config*/
  struct sockaddr_in server_address; /*struct for the address*/
  server_address.sin_family = AF_INET; /*gets the domain type*/
  server_address.sin_port = htons(9001); /*the port to connect*/
  server_address.sin_addr.s_addr = INADDR_ANY; /*the ip*/

  /*sets the server with the struct*/
  int err = bind(serv_sock, (struct sockaddr *)&server_address,
                 sizeof(server_address));
  if (err == -1) { /*catch errs*/
    fprintf(stderr, "Could not bind\n");
    exit(8);
  }
  
  listen(serv_sock, 5); /*num of treadhs*/

  /*dealing with the client*/  
  int client_sock;
  client_sock = accept(serv_sock, NULL, NULL);/*connects with client*/

  send(client_sock, serv_msg, sizeof(serv_msg), 0); /*send the message*/

  close(serv_sock);/*close your files*/
  close(client_sock); /*close your files*/

  return 0;
 }
