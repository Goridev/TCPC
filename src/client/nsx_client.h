#include <arpa/inet.h>
#include "../core/nsx_cmd.h"

typedef struct nsx_client nsx_client;
struct nsx_client 
{
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    nsx_client (*socket_create)(nsx_client *);
    nsx_client (*connected)(nsx_client *);
    nsx_client (*loop)(nsx_client *);
    nsx_client (*close)(nsx_client *);
};

nsx_client nsx_client_socket_create(nsx_client *self)
{
    
    if (self->sockfd == -1) {
        printf(""CLIENT_LOG" socket creation failed...\n");
        exit(0);
    }
    else
        printf(""CLIENT_LOG" socket created\n");
}
nsx_client nsx_client_connected(nsx_client *self)
{
    if (connect(self->sockfd, (SA*)&self->servaddr, sizeof(self->servaddr)) != 0) {
        printf(""CLIENT_LOG" server refused...\n");
        exit(0);
    }
    else
        printf(""CLIENT_LOG" server accepted\n");
}
nsx_client nsx_client_loop(nsx_client *self)
{
    int n;
    nsx_cmd cmd;
    cmd.exit = nsx_cmd_exit;

    for (;;) {
        bzero(cmd.buffer, sizeof(cmd.buffer));
        printf("\t "CLIENT_LOG" "CLIENT_TO_SERVER": ");
        n = 0;
        while ((cmd.buffer[n++] = getchar()) != '\n');
        write(self->sockfd, cmd.buffer, sizeof(cmd.buffer));
        bzero(cmd.buffer, sizeof(cmd.buffer));
        read(self->sockfd, cmd.buffer, sizeof(cmd.buffer));
        printf(""CLIENT_LOG" "CLIENT_FROM_SERVER": %s", cmd.buffer);
        // if ((strncmp(buff, "exit", 4)) == 0) {
        //     printf(""CLIENT_LOG" Client Exit...\n");
        //     break;
        // }
        cmd.exit(&cmd);
        //
    }
}
nsx_client nsx_client_close(nsx_client *self)
{
    close(self->sockfd);
}