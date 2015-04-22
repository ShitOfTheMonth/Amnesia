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

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "amnesia_list.h"
#include "amnesia_socket.h"

amnesia_socket *amnesia_create_socket(char *addr, int port)
{
  /* Constuct the servaddr_in struct */
  struct sockaddr_in _servaddr;
  bzero(&_servaddr, sizeof(_servaddr));

  _servaddr.sin_family = AF_INET;
  _servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  _servaddr.sin_port = htons(port);

  int _sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bind(_sockfd, (struct sockaddr *)&_servaddr, sizeof(_servaddr));

  listen(_sockfd, 1024);

  amnesia_socket *socket = malloc(sizeof(amnesia_socket));

  socket->sockfd = _sockfd;
  socket->servaddr = &_servaddr;
  socket->clients = amnesia_list_new();

  return socket;
}

void amnesia_free_socket(amnesia_socket *socket)
{
  amnesia_list_free(socket->clients); /* Free linked list and their children */

  free(socket->servaddr);
  free(socket);
}
