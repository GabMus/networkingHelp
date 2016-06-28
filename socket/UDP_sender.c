/* UDP sender */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RECV_PORT 7550
#define RECV_IP "127.0.0.1"

main()
{ int sockfd;
  struct sockaddr_in recv_addr;
  extern int errno;
  int i,n;
  char line[100];

  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }
  
  memset( &recv_addr,0, sizeof(recv_addr));
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_addr.s_addr = inet_addr(RECV_IP);
  recv_addr.sin_port = htons(RECV_PORT);
  
  printf("\nInserisci un numero intero ");
  scanf("%d",&n);

  for(i=0;i<10;++i)
  { sprintf(line,"\n %d",i+n);
    printf("%s",line);
    sendto(sockfd, line, strlen(line)+1, 0, (struct sockaddr *)&recv_addr, sizeof(recv_addr));
  }
}
