#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

// error handling function
void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, new_sock; // socket and new socket descriptor
    struct sockaddr_in server_address, client_address; // server and client address structure
    char buffer[256]; // buffer to store the random number
    int random_number; // variable to store the random number
    int n; // variable to check for errors

    // creating socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening socket");

    // setting up server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // binding socket to the address and port
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) 
        error("Error on binding");

    // listening for incoming connections
    listen(sockfd, 5);
    socklen_t client_length = sizeof(client_address);
    new_sock = accept(sockfd, (struct sockaddr *) &client_address, &client_length);
    if (new_sock < 0) 
        error("Error on accept");

    // generating random number between 100 and 999
    srand(time(NULL));
    random_number = (rand() % 900) + 100;

    // storing the number as a string in the buffer
    sprintf(buffer, "%d", random_number);

    // sending the number to the client
    n = write(new_sock, buffer, sizeof(buffer));
    if (n < 0) error("Error writing to socket");

    // closing the socket
    close(new_sock);
    close(sockfd);
    return 0;
}
