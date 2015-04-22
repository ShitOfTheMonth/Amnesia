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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "amnesia.h"
#include "amnesia_socket.h"

/* This should be provided by our make task */
#ifndef VERSION
#define VERSION "unknown"
#endif

/* Let's begin this shit */
#define AMNESIA_CONN_BUFFER_SIZE 1024

#define AMNESIA_MAX_BINDHOST_LEN 64

#define AMNESIA_DEFAULT_SOCK_ADDR "0.0.0.0"
#define AMNESIA_DEFAULT_SOCK_PORT 6789

int main(int argc, char **argv)
{
  char ascii_poop[512];
  strcpy(ascii_poop, "     ~'. _^ _ '~   \n");
  strcat(ascii_poop, "     ~' (____) '~  \n");
  strcat(ascii_poop, "     ~'(______) '~ \n");
  strcat(ascii_poop, "     '(________) '~\n");
  strcat(ascii_poop, "     (__________)  \n");

  /* CLI argument variables */
  char usage_str[256];
  strcpy(usage_str, "Amnesia (version %s) - (C) 2015 ShitOfTheMonth\n\n");
  strcat(usage_str, "Usage: %s [-b <host>] [-p <port>]\n");

  char hostname_err_str[] = "Hostname is too long. Maximum of %d characters.\n";
  char output_str[255];

  char opt_host[AMNESIA_MAX_BINDHOST_LEN] = AMNESIA_DEFAULT_SOCK_ADDR;
  int opt_port = AMNESIA_DEFAULT_SOCK_PORT;

  while(1) {
    char c;

    if((c = getopt(argc, argv, "hb:p:")) != -1) {
      switch(c) {
        case 'b':
          if(strlen(optarg) > AMNESIA_MAX_BINDHOST_LEN) {
            sprintf(output_str, hostname_err_str, AMNESIA_MAX_BINDHOST_LEN);

            amnesia_exit(output_str, AMNESIA_MAX_BINDHOST_LEN);
          }

          strncpy(opt_host, optarg, AMNESIA_MAX_BINDHOST_LEN - 1);
          opt_host[AMNESIA_MAX_BINDHOST_LEN - 1] = '\0'; /* set last char to null */

          break;
        case 'p':
          if((opt_port = atoi(optarg)) <= 1024) {
            amnesia_exit("Invalid port number, must be >1024.\n", EXIT_FAILURE);
          }

          break;
        case 'h':
        case '?':
        default:
          sprintf(output_str, usage_str, VERSION, argv[0]);

          amnesia_exit(output_str, 0);
      }
    } else {
      /* Parsed everything */
      break;
    }
  }

  /* Construct the socket */
  int n, conn_fd;
  char mesg[AMNESIA_CONN_BUFFER_SIZE];
  pid_t child_pid;
  socklen_t client_len;

  printf("%s\n [ Shit of the Month ]\n [    April 2015     ]\n", ascii_poop);
  printf("\nStarting Amnesia on %s:%d\n", opt_host, opt_port);
  amnesia_socket *sock = amnesia_create_socket(opt_host, opt_port);

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

void amnesia_exit(char *msg, int code)
{
  if(code < 0 || code > 255) {
    code = EXIT_FAILURE; /* 1 */
  }

  if(msg != NULL)
    printf("%s", msg);

  exit(code);
}
