/* receiver */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define RECV_PORT 7550

main()
{ int sockfd;
  struct sockaddr_in recv_addr, send_addr;
  //extern int errno;
  socklen_t l = sizeof(send_addr);
  char line[100];
  
  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }
  memset((char *) &recv_addr,0,sizeof(recv_addr));
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  recv_addr.sin_port = htons(RECV_PORT);

  if(bind(sockfd, (struct sockaddr *) &recv_addr, sizeof(send_addr))<0)
  { printf("\nErrore nel binding. Errore %d \n",errno);
    return -1;
  }
  
  for(;;)
  { recvfrom(sockfd, line, 99,0, (struct sockaddr *)&send_addr,&l);
    printf("%s",line);
  }
}
