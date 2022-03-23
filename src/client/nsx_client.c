#include "nsx_client.h"
   
int main(int argc, const char * argv[])
{
    nsx_client client;
    client.socket_create = nsx_client_socket_create;
    client.connected = nsx_client_connected;
    client.loop = nsx_client_loop;
    client.close = nsx_client_close;

    // socket create and verification
    client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    client.socket_create(&client);
    bzero(&client.servaddr, sizeof(client.servaddr));
   
    // assign IP, PORT
    client.servaddr.sin_family = AF_INET;
    client.servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    client.connected(&client);
    // function for chat
    // func(client.sockfd);
    client.loop(&client);
   
    // close the socket
    // close(client.sockfd);
    client.close(&client);
}