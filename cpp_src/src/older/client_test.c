#include "socket_test.h"

int main(int argc ,char *argv[])
{
    int sockfd = 0, n = 0;
    char revBuff[1024];
    struct sockaddr_in serv_addr;

    if( argc !=2 )
    {
        printf("\n Usage: %s < ip of server > \n", argv[0]);
        return 1;
    }

    memset(revBuff,'0',sizeof(revBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    
    memset(&serv_addr,'0',sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf( "\n inet_pron error occured! \n");
        return 1;
    }

    if(connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("\n Error: connect Failed! \n");
        return 1;
    }
    while((n = read(sockfd, revBuff, sizeof(revBuff)-1)) > 1)
    {
        revBuff[n] = 0;
        if(fputs(revBuff, stdout) == EOF )
        {
            printf("\n Error : Fputs error \n");
        }
    }

    if( n < 0)
    {
        printf("\n Read Error \n");
    }

    return 0;
}
