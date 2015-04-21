#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "amnesia.h"
#include "amnesia_socket.h"

#define AMNESIA_CONN_BUFFER_SIZE 1024

int main(int argc, char **argv)
{
  int n, conn_fd;
  char mesg[AMNESIA_CONN_BUFFER_SIZE];
  pid_t child_pid;
  socklen_t client_len;

  /* Construct the socket */
  amnesia_socket *sock = amnesia_create_socket("0.0.0.0", 6789);

  struct sockaddr_in client_addr;

  /* Begin accepting connections */
  for(;;)
  {
    client_len = sizeof(client_addr);

    conn_fd = accept(sock->sockfd, (struct sockaddr *) &client_addr, &client_len);

    if((child_pid = fork()) == 0)
    {
      close(sock->sockfd);

      for(;;)
      {
        n = recvfrom(conn_fd, mesg, AMNESIA_CONN_BUFFER_SIZE, 0,
              (struct sockaddr *)&client_addr, &client_len);

        sendto(conn_fd, mesg, n, 0, (struct sockaddr *)&client_addr, client_len);

        mesg[n] = 0; // Overwrite \0?
        printf("<< %s", mesg);
      }
    }

    close(conn_fd);
  }
}
