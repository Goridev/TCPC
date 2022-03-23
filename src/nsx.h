#include "client/nsx_client.h"
#include "server/nsx_server.h"

void multiplexClient(FILE *fp, int sockfd, char inbuffer[], char outbuffer[])
{
    int maxfd;
    fd_set rset;

    FD_ZERO(&rset);
    for(;;)
    {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfd = std::max(fileno(fp), sockfd) + 1;

        int res = select(maxfd, &rset, NULL, NULL, NULL);

        if(res < 0)
        {
            printf("'select error\n");
        }

        if(FD_ISSET(sockfd, &rset))
        {
            if(read(sockfd, inbuffer, sizeof(inbuffer)) == 0)
                printf("read error\n");
            printf("Received: %s\n", inbuffer);
            fflush(stdout);
                memset(inbuffer, 0, sizeof(inbuffer));
        }

        else if(FD_ISSET(fileno(fp), &rset))
        {
            fprintf(stdout, "\n> ");
            if(fgets(outbuffer, sizeof(outbuffer), fp) == NULL)
                return;
            write(sockfd, outbuffer, strlen(outbuffer));
            printf("Send: %s\n", outbuffer);
            fflush(stdout);
                memset(outbuffer, 0, sizeof(outbuffer));
        }
    }
}