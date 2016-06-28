
/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{
   int listenfd,connfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   char mesg[1000];

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(32000);
   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,5);

   for(;;)
   {
      clilen=sizeof(cliaddr);
      connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);
	  
      if (fork() == 0)
      {
         close (listenfd);
		
         for(;;)
         {
            n = recv(connfd,mesg,1000,0);
            send(connfd,mesg,n,0);
            mesg[n] = 0;
            printf("\nPid = %d: received from port %d the following:\n",getpid(),ntohs(cliaddr.sin_port));
            printf("%s",mesg);
            printf("-------------------------------------------------------\n");
         }
         
      }
      close(connfd);
   }
}
