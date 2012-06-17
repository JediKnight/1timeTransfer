#ifndef _MAIL_H_
#define _MAIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#undef NULSTR
#define NULSTR '\0'
#undef CRLF
#define CRLF "\r\n"

typedef struct { char serv[64]; int port; char from[64]; char to[64]; char subject[64]; char message[1024]; } Mail_Data;

int sendm(Mail_Data mdata);

#endif /* _MAIL_H_ */
