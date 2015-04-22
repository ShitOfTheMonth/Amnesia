#ifndef AMNESIA_H
#define AMNESIA_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

typedef struct _client amnesia_client;

struct _client
{
  /* TODO */
};

int main(int argc, char **argv);
extern void amnesia_exit(char *msg, int code);

#endif /* AMNESIA_H */
