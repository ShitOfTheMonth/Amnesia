#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "amnesia.h"

amnesia_socket amnesia_create_socket(void)
{
    amnesia_socket *socket = malloc(sizeof(amnesia_socket));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Check the socket was created successfully.
    if(sockfd > 0) {
      return NULL;
    }

    socket->sockfd = sockfd;
}
