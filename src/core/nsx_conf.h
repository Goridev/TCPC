#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>


#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h>  //FD_SET, FD_ISSET, FD_ZERO macros
#include <netinet/in.h> 

#ifndef tcp_conf_h
#define tcp_conf_h

#define TRUE   1 
#define FALSE  0 
#define MAX 80
#define PORT 8080
#define HOST "127.0.0.1"
#define SA struct sockaddr


#define FGBLACK(string) "\x1b[30m" string "\x1b[0m"
#define FGRED(string) "\x1b[31m" string "\x1b[0m"
#define FGGREEN(string) "\x1b[32m" string "\x1b[0m"
#define FGYELLOW(string) "\x1b[33m" string "\x1b[0m"
#define FGBLUE(string) "\x1b[34m" string "\x1b[0m"
#define FGMAGENTA(string) "\x1b[35m" string "\x1b[0m"
#define FGCYAN(string) "\x1b[36m" string "\x1b[0m"
#define FGWHITE(string) "\x1b[37m" string "\x1b[0m"

#define BGBLACK(string) "\x1b[40m" string "\x1b[0m"
#define BGRED(string) "\x1b[41m" string "\x1b[0m"
#define BGGREEN(string) "\x1b[42m" string "\x1b[0m"
#define BGYELLOW(string) "\x1b[43m" string "\x1b[0m"
#define BGBLUE(string) "\x1b[44m" string "\x1b[0m"
#define BGMAGENTA(string) "\x1b[45m" string "\x1b[0m"
#define BGCYAN(string) "\x1b[46m" string "\x1b[0m"
#define BGWHITE(string) "\x1b[47m" string "\x1b[0m"

#define SERVER_LOG "["FGRED("Server-TCP")"]"
#define CLIENT_LOG "["FGYELLOW("Client-TCP")"]"

#define CLIENT_FROM_SERVER "{"FGRED("From Server")"}"
#define CLIENT_TO_SERVER "{"FGBLUE("To server")"}"

#endif