#include "mail.h"
#include "network.h"

int sendm(Mail_Data mdata)
{
  sock soc;
  int i;
  char req[6][1024];

  sprintf(req[0], "helo bamboo-copter.com\r\n");
  sprintf(req[1], "mail from:%s\r\n", mdata.from);
  sprintf(req[2], "rcpt to:%s\r\n", mdata.to);
  sprintf(req[3], "data\r\n");
  sprintf(req[4], "From: %s\nSubject: %s\n%s\r\n.\r\n", mdata.from, mdata.subject, mdata.message);
  sprintf(req[5], "quit\r\n");

  soc = getsock(mdata.serv, mdata.port);

  for(i = 0; i < (sizeof(req) / sizeof(req[0])); request(soc, req[i++]));

  sclose(soc);

  return 0;
}
