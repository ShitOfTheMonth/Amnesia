/*
 * Copyright (c) 2015 ShitOfTheMonth.
 *
 * Amnesia is a key/value store that forgets everything you
 * send it.
 *
 * Authors: Evan Darwin <evan@devil.io>
 * 					Chazz Wolcott <emokitty@limun.org>
 *
 * Released under the MIT license, available in the LICENSE file.
 */

#ifndef AMNESIA_SOCKET_H
#define AMNESIA_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "amnesia_list.h"

typedef struct _amnesia_socket amnesia_socket;

struct _amnesia_socket {
  int sockfd;                   /* Sock file descriptor */
  struct sockaddr_in *servaddr; /* The sockaddr_in information for this socket */

  amnesia_list *clients;        /* The linked list of our clients */
} _amnesia_socket;

extern amnesia_socket *amnesia_create_socket(char *addr, int port);
extern void amnesia_free_socket(amnesia_socket *socket);

#endif /* AMNESIA_SOCKET_H */
