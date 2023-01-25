#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// error handling function
void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd; // socket descriptor
    struct sockaddr_in server_address; // server address structure
    char buffer[256]; // buffer to store the random number
    int n; // variable to check for errors

    // creating socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening socket");

    // setting up server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.56.102");
    server_address.sin_port = htons(8080);

    // connecting to the server
    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        error("Error connecting");

    // clearing the buffer
    bzero(buffer, sizeof(buffer));

    // reading the random number from the server
    n = read(sockfd, buffer, sizeof(buffer)-1);
    if (n < 0) 
        error("Error reading from socket");
        
    // print the random number
    printf("Random number: %s\n", buffer);

    // close the socket
    close(sockfd);
    return 0;
}