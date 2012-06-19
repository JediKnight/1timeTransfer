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
  char m[1024], a[64], *b, *p;

  fp = fopen("/tmp/maillog", "a+");

  while(fgets(m, 1024, stdin))
    {
      if((b = strstr(m, "Return-Path: ")))
	{
	  strtok(b, "<");
	  b = strtok(NULL, ">");
	  strncpy(mdata.from, b, strlen(b));

	  while(fgets(a, 64, fp))
	    {
	      /* 文字列の先頭から改行文字を検索 */
	      if((p = strchr(a, '\n')) != NULL) *p = '\0';
	      printf("mdata.from => %-30s:%d\n", mdata.from, (int)strlen(mdata.from));
	      printf("p          => %-30s:%d\n", p, (int)strlen(p));

	      if(strncmp(mdata.from, p, strlen(p)) == 0 && strlen(p) > 0)
		{
		  printf("break!!");
		  goto end;
		}
	    }
	}

      else if((b = strstr(m, "Subject: ")))
	{
	  strtok(b, " ");
	  b = strtok(NULL, " ");
	  strncpy(mdata.subject, b, strlen(b));
	}

      else if(strcmp(m, "") == 0 || mflg == READ)
	{
	  mflg = READ;
	  strcat(mdata.message, m);
	}

      i++;
    }

  fprintf(fp, "%s\n", mdata.from);

  sendm(mdata);

 end:
  fclose(fp);

  return 0;
}
