#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

typedef int sock;

#define BUF_LEN 1024

int getsock(char *hostnm, int portn);
int request(int soc, char *path);
int getmsg(int soc);
int sclose(int soc);

#endif /* _NETWORK_H_ */
