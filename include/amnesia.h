#ifndef AMNESIA_H
#define AMNESIA_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "amnesia_list.h"

typedef struct _client amnesia_client;
typedef struct _socket amnesia_socket;

struct _client
{
  /* TODO */
}

struct _socket
{
  int sockfd
}

extern amnesia_socket amnesia_create_socket(void);

#endif /* AMNESIA_H */
