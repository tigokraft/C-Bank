#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>

#include "components/header.h"

#define MAX 200
#define PORT 2000
#define SA struct sockaddr

// Struct to hold client information
struct client_info
{
    int connfd;
    char ip_addr[INET_ADDRSTRLEN];
};

// Function for chat with each client in a separate thread
void *func(void *arg)
{
    struct client_info *cli = (struct client_info *)arg;
    char buff[MAX];
    char *packet;
    char *tmp;
    bool validation;
    bool connected = true;

    printf("Connected to client: %s\n", cli->ip_addr);

    while (connected)
    {
        bzero(buff, MAX);

        // Read message from client
        int bytesRead = read(cli->connfd, buff, sizeof(buff));


        // Handle disconnection or error
        if (bytesRead <= 0)
        {
            printf("Client %s disconnected\n", cli->ip_addr);
            connected = false;
        }
        else
        {
            if (isdigit(buff[0])) {
                printf("\nbytes received: %d\n", bytesRead);
                tmp = strdup(buff);
                // Print message with client IP and get server response
                printf("From %s: %s\n", cli->ip_addr, tmp);
                bzero(buff, MAX);

                packet = handle(tmp); // Assign the returned char* directly
                free(tmp);            // Free the memory allocated by strdup

                printf("result = %s\n", packet);
                // Send response to client (packet is now a char *)
                write(cli->connfd, packet, strlen(packet));
            }
            else {
                printf("BOT TRAFFIC DETECTED!!!\n");
                write(cli->connfd, "404", 3);
            }
        }
    }

    close(cli->connfd);
    free(cli);
    pthread_exit(NULL);
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket creation failed");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("socket bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(sockfd, 5) != 0)
    {
        perror("Listen failed");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    while (true)
    {
        struct client_info *cli = malloc(sizeof(*cli)); // Allocate for client_info
        pthread_t thread;

        // Accept connection
        struct sockaddr_in client_addr; // Declare a separate sockaddr_in struct
        socklen_t len = sizeof(client_addr);
        cli->connfd = accept(sockfd, (SA *)&client_addr, &len);
        if (cli->connfd < 0)
        {
            perror("server accept failed");
            free(cli); // Free memory if accept fails
            continue;
        }

        // Get client's IP address
        inet_ntop(AF_INET, &client_addr.sin_addr, cli->ip_addr, INET_ADDRSTRLEN);

        // Create a new thread to handle the client
        if (pthread_create(&thread, NULL, func, (void *)cli) != 0)
        {
            perror("pthread_create failed");
            close(cli->connfd);
            free(cli);
        }

        // Detach thread
        pthread_detach(thread);
    }

    // Close socket (only works when there is an error)
    close(sockfd);
    return 0;
}