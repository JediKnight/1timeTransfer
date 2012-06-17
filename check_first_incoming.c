#include "check_first_incoming.h"
#include "mail.h"

int main()
{
  Mail_Data mdata = { .serv = "localhost",
		      .port = 25,
		      .from[0] = NULSTR,
		      .to = MYADDR,
		      .subject[0] = NULSTR,
		      .message[0] = NULSTR };
  FILE *fp;
  int i = 0;
  boolean mflg = UNREADY;
  char m[1024], a[64], *b;

  fp = fopen("/tmp/maillog", "a+");

  while(fgets(m, 1024, stdin))
    {
      if((b = strstr(m, "Return-Path: ")))
	{
	  strtok(b, "<");
	  b = strtok(NULL, ">");
	  strncpy(mdata.from, b, strlen(b));

	  while(fgets(a, 64, fp))
	    if(strcmp(mdata.from, a) == 0 &&
	       strstr(mdata.from, a) != NULL) goto end;
	}

      else if((b = strstr(m, "Subject: ")))
	{
	  strtok(b, " ");
	  b = strtok(NULL, " ");
	  strncpy(mdata.subject, b, strlen(b));
	}

      else if(strcmp(m, "") == 0 || mflg == READ)
	{
	  if(mflg == UNREADY) mflg = READY;
	  else if(mflg == READY) mflg = READ;
	  else strcat(mdata.message, m);
	}

      i++;
    }

  fprintf(fp, "%s", mdata.from);

  sendm(mdata);

 end:
  fclose(fp);

  return 0;
}
