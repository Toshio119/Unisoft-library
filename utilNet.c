#include "utilNet.h"

//  to create a TCP socket
int create_tcp_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

//  to create a UDP socket
int create_udp_socket() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

//  to bind a socket to an address and port
int bind_socket(int sockfd, const char *address, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        return -1;
    }
    return 0;
}

//  to listen for incoming connections on a TCP socket
int listen_socket(int sockfd, int backlog) {
    if (listen(sockfd, backlog) < 0) {
        perror("Listen failed");
        return -1;
    }
    return 0;
}

// to accept an incoming connection on a TCP socket
int accept_connection(int sockfd, struct sockaddr_in *client_addr) {
    socklen_t addr_len = sizeof(*client_addr);
    int new_sockfd = accept(sockfd, (struct sockaddr *)client_addr, &addr_len);
    if (new_sockfd < 0) {
        perror("Accept failed");
    }
    return new_sockfd;
}

//  to connect to a server using a TCP socket
int connect_to_server(int sockfd, const char *address, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);
    addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connect failed");
        return -1;
    }
    return 0;
}

//  to send data over a socket
ssize_t send_data(int sockfd, const void *data, size_t size) {
    ssize_t bytes_sent = send(sockfd, data, size, 0);
    if (bytes_sent < 0) {
        perror("Send failed");
    }
    return bytes_sent;
}

// to receive data from a socket
ssize_t receive_data(int sockfd, void *buffer, size_t size) {
    ssize_t bytes_received = recv(sockfd, buffer, size, 0);
    if (bytes_received < 0) {
        perror("Receive failed");
    }
    return bytes_received;
}

//  to close a socket
void close_socket(int sockfd) {
    close(sockfd);
}

// Utility function to resolve a hostname to an IP address
int resolve_hostname(const char *hostname, char *ip_address, size_t size) {
    struct addrinfo hints, *res;
    int status;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "Getaddrinfo failed: %s\n", gai_strerror(status));
        return -1;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    inet_ntop(res->ai_family, &(ipv4->sin_addr), ip_address, size);

    freeaddrinfo(res);
    return 0;
}
