//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux  
#include "nsx_server.h"
     
int main(int argc , char *argv[])
{
    multi multi;
    multi.opt = TRUE;  
    // multi.client_socket[MAX_CLIENT];
    // multi.max_clients = MAX_CLIENT;

    // int master_socket , addrlen , new_socket , client_socket[30] ,max_clients = 30 , activity, i , valread , sd;  
    // int max_sd;
    // struct sockaddr_in address;  
         
    // Name response
    // char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
    // fd_set readfds;  
         
    //a message 
    // char *message = "ECHO Daemon v1.0 \r\n";  
     
    //initialise all client_socket[] to 0 so not checked 
    for (multi.i = 0; multi.i < multi.max_clients; multi.i++)  
    {  
        multi.client_socket[multi.i] = 0;  
    }  
         
    //create a master socket 
    if( (multi.master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(multi.master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&multi.opt, sizeof(multi.opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    multi.address.sin_family = AF_INET;  
    multi.address.sin_addr.s_addr = INADDR_ANY;  
    multi.address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(multi.master_socket, (struct sockaddr *)&multi.address, sizeof(multi.address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(multi.master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    multi.addrlen = sizeof(multi.address);  
    puts("Waiting for connections ...");  
         
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&multi.readfds);  
     
        //add master socket to set 
        FD_SET(multi.master_socket, &multi.readfds);  
        multi.max_sd = multi.master_socket;  
             
        //add child sockets to set 
        for ( multi.i = 0 ; multi.i < multi.max_clients ; multi.i++)  
        {  
            //socket descriptor 
            multi.sd = multi.client_socket[multi.i];  
                 
            //if valid socket descriptor then add to read list 
            if(multi.sd > 0)  
                FD_SET( multi.sd , &multi.readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(multi.sd > multi.max_sd)  
                multi.max_sd = multi.sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        multi.activity = select( multi.max_sd + 1 , &multi.readfds , NULL , NULL , NULL);  
       
        if ((multi.activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(multi.master_socket, &multi.readfds))  
        {  
            if ((multi.new_socket = accept(multi.master_socket, (struct sockaddr *)&multi.address, (socklen_t*)&multi.addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , multi.new_socket , inet_ntoa(multi.address.sin_addr) , ntohs(multi.address.sin_port));
           
            //send new connection greeting message 
            if( send(multi.new_socket, multi.response, strlen(multi.response), 0) != strlen(multi.response) )  
            {  
                perror("send");  
            }  
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (multi.i = 0 ; multi.i < multi.max_clients; multi.i++)  
            {  
                //if position is empty 
                if( multi.client_socket[multi.i] == 0 )  
                {  
                    multi.client_socket[multi.i] = multi.new_socket;  
                    printf("Adding to list of sockets as %d\n" , multi.i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (multi.i = 0; multi.i < multi.max_clients; multi.i++)  
        {  
            multi.sd = multi.client_socket[multi.i];  
                 
            if (FD_ISSET( multi.sd , &multi.readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((multi.read = read( multi.sd , multi.buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(multi.sd , (struct sockaddr*)&multi.address ,(socklen_t*)&multi.addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(multi.address.sin_addr) , ntohs(multi.address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( multi.sd );  
                    multi.client_socket[multi.i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    multi.buffer[multi.read] = '\0';  
                    send(multi.sd , multi.buffer , strlen(multi.buffer) , 0 );  
                }  
            }  
        }  
    }     
    return 0;  
}  