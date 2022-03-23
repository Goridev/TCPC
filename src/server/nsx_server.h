#include <netinet/in.h>
#include <sys/types.h>
#include "../core/nsx_cmd.h"

typedef struct nsx_server nsx_server;
struct nsx_server {
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    nsx_server (*listen)(nsx_server *);
    nsx_server (*socket_create)(nsx_server *);
    nsx_server (*socket_binding)(nsx_server *);
    nsx_server (*accept_client)(nsx_server *);
    nsx_server (*loop)(nsx_server *);
    nsx_server (*close)(nsx_server *);
};
// typedef nsx_server *p_nsx_server;

nsx_server nsx_server_listen(nsx_server *self)
{
    if(listen(self->sockfd, 5) != 0)
    {
        printf(""SERVER_LOG" listen failed...\n");
        exit(0);
    }
    else
        printf(""SERVER_LOG" listen\n");
}
nsx_server nsx_server_socket_create(nsx_server *self)
{
    if (self->sockfd == -1) {
        printf(""SERVER_LOG" socket creation failed...\n");
        exit(0);
    }
    else
        printf(""SERVER_LOG" socket created\n");
}
nsx_server nsx_server_socket_binding(nsx_server *self)
{
    if ((bind(self->sockfd, (SA*)&self->servaddr, sizeof(self->servaddr))) != 0) {
        printf(""SERVER_LOG" socket binding failed...\n");
        exit(0);
    }
    else
        printf(""SERVER_LOG" socket binded\n");
}
nsx_server nsx_server_accept_client(nsx_server *self)
{
    if (self->connfd < 0) {
        printf(""SERVER_LOG" client refused...\n");
        exit(0);
    }
    else
        printf(""SERVER_LOG" client accepted\n");
}
nsx_server nsx_server_loop(nsx_server *self)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(self->connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf(""SERVER_LOG" {From client}: %s\t "SERVER_LOG" {To client} : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
   
        // and send that buffer to client
        write(self->connfd, buff, sizeof(buff));
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf(""SERVER_LOG" server Exit...\n");
            break;
        }
    }
}
nsx_server nsx_server_close(nsx_server *self)
{
    close(self->sockfd);
}