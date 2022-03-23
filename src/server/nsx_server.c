#include "nsx_server.h"
 
int main(int argc,char * argv[])
{
    nsx_server server;
    /*
    * Define Multiple method binded to server
    */
    server.listen = nsx_server_listen;
    server.socket_create = nsx_server_socket_create;
    server.socket_binding = nsx_server_socket_binding;
    server.accept_client = nsx_server_accept_client;
    server.loop = nsx_server_loop;
    server.close = nsx_server_close;

    // socket create and verification
    server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.socket_create(&server);
    bzero(&server.servaddr, sizeof(server.servaddr));

    // assign IP, PORT
    server.servaddr.sin_family = AF_INET;
    server.servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server.servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    server.socket_binding(&server);

    // Now server is ready to listen and verification
    server.listen(&server);
    server.len = sizeof(server.cli);

    // Accept the data packet from client and verification
    server.connfd = accept(server.sockfd, (SA*)&server.cli, &server.len);
    server.accept_client(&server);

    // Function for chatting between client and server
    // func(server.connfd);
    server.loop(&server);
   
    // After chatting close the socket
    server.close(&server);
}