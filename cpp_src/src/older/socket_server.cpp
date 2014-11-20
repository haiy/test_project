/*
 * Only for socket programming test !
 * haiy
 * http://www.thegeekstuff.com/2011/12/c-socket-programming/
 * Tue Nov  5 09:35:16 CST 2013
 * */
#include "socket_test.h"
int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff,'0',sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    serv_addr.sin_port = htons(5000);
    
    bind(listenfd, (struct sockaddr  *)&serv_addr,sizeof(serv_addr));

    listen(listenfd,10);

    while(1)
    {
        connfd = accept(listenfd,(struct sockaddr *)NULL,NULL);
        ticks = time(NULL);
        snprintf(sendBuff,sizeof(sendBuff),"%.24s\r\n",ctime(&ticks));
        write(connfd,sendBuff,strlen(sendBuff));

        close(connfd);
        sleep(1);
    }
}

