#ifndef UTILNET_H
#define UTILNET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
/*
===================================================
       U!nisoft Libarary's 
       Utility at it's peak
---------------------------------------------------
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##             ##   #
  ##    ##  ##   ##        ##   ##   #
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##        ##   ##   #
  ##    ##       ##        ##   ##   #
    ####    ##   ########  ##   #####
---------------------------------------------------
© 2024 Unisoft .All rights reserved.
For support, contact: toshiojp119@gmail.com
===================================================
*/

int create_tcp_socket();
int create_udp_socket();
int bind_socket(int sockfd, const char *address, int port);
int listen_socket(int sockfd, int backlog);
int accept_connection(int sockfd, struct sockaddr_in *client_addr);
int connect_to_server(int sockfd, const char *address, int port);
ssize_t send_data(int sockfd, const void *data, size_t size);
ssize_t receive_data(int sockfd, void *buffer, size_t size);
void close_socket(int sockfd);
int resolve_hostname(const char *hostname, char *ip_address, size_t size);

#endif // UTILNET_H
