#include "check_first_incoming.h"
#include "mail.h"

int addlog(const char *addr)
{
  FILE *fp;

  fp = fopen("/tmp/maillog", "a");
  fprintf(fp, "%s\n", addr);
  fclose(fp);

  return 0;
}

boolean searchlog(const char *addr)
{
  FILE *fp;
  boolean flg = FALSE;
  char *ptr;
  char buf[ADLEN];

  fp = fopen("/tmp/maillog", "r");
  while(fgets(buf, ADLEN, fp))
    {
      if((ptr = strchr(buf, '\n')) != NULL) *ptr = '\0';
      if(strncmp(addr, ptr, strlen(ptr)) == 0) flg = TRUE;
    }
  
  fclose(fp);
  
  return flg;
}

int main()
{
  Mail_Data md = { .serv = "localhost", .port = 25, .from[0] = NULSTR, .to = MYADDR, .subject[0] = NULSTR, .message[0] = NULSTR };
  boolean rflg = FALSE;;
  char *mdata;
  char *addr;

  while(fgets(mdata, MSIZE, stdin))
    {
      if((addr = strstr(mdata, "Return-Path: ")))
	{
	  strtok(mdata, "<");
	  addr = strtok(NULL, ">");
	  strncpy(md.from, addr, strlen(addr));
	  if(searchlog(md.from)) goto end;
	}

      else if((addr = strstr(mdata, "Subject: ")))
	{
	  strtok(addr, " ");
	  addr = strtok(NULL, " ");
	  strncpy(md.subject, addr, strlen(addr));
	}

      else if(strcmp(mdata, "") == 0 || rflg == TRUE)
	{
	  rflg = TRUE;
	  strcat(md.message, mdata);
	}
    }

  sendm(md);

 end:

  return 0;
}
