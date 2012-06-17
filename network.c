#include "network.h"

sock getsock(char *hostnm, int portn)
{
  struct hostent *host;
  struct sockaddr_in sockaddr;

  int soc;

  /* struct hostent FAR * gethostbyname(const char FAR * name) */
  if((host = gethostbyname(hostnm)) == NULL)
    {
      fprintf(stderr, "gethostbyname: %s\n", hostnm);
      exit(EXIT_FAILURE);
    }

  /*
   * ゼロクリア
   * memset(void *s, int , size_t)
   */
  memset(&sockaddr, 0, sizeof(sockaddr));

  /*
   * sockaddr.sin_familyをセット
   */
  sockaddr.sin_family = PF_INET;

  /*
   * sockaddr.sin_addrをセット
   * memcpy(void *dst, const void *src, size_t) 
   */
  memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);

  /*
   * sockadder.sin_portをセット
   */
  sockaddr.sin_port = htons(portn);

  /*
   * socket生成
   * socket(int domain, int type, int protocol)
   * PF_INET IPv4
   * SOCK_STREAM 順序性と信頼性があり、双方向の接続されたバイトストリームを提供
   */
  if((soc = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      fprintf(stderr, "socket");
      close(soc);
      exit(EXIT_FAILURE);
    }

  /*
   * コネクションを確立する
   * connect(int socket, const struct sockaddr *address, socklen_t address_len)
   */
  if(connect(soc, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
      fprintf(stderr, "connect");
      close(soc);
      exit(EXIT_FAILURE);
    }

  return soc;
}

int request(int soc, char *req)
{
  char msg[BUF_LEN];

  /* 
   * リクエスを生成 
   */
  snprintf(msg, sizeof(msg), "%s", req);

  /*
   * リクエストの送信
   * write(int socket, const void *buf, size_t nbyte)
   */
  write(soc, msg, strlen(msg));

  return 0;
}

int getmsg(int soc)
{
  char buf[BUF_LEN];

  /*
   * メッセージの受信
   * read(int socket, void *buf, size_t nbyte)
   */
  while(read(soc, buf, sizeof(buf)) > 0)
    {
      printf("%s", buf);
    }

  return 0;
}

int sclose(int soc)
{
  close(soc);

  return 0;
}
