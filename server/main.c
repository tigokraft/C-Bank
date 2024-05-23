#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>  // For inet_ntoa()
#include <pthread.h>   // For multi-threading

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Struct to hold client information
struct client_info {
    int connfd;
    char ip_addr[INET_ADDRSTRLEN];
};

// Function designed for chat with each client in a separate thread
void *func(void *arg)
{
    struct client_info *cli = (struct client_info *)arg;
    char buff[MAX];
    int n;

    // Get client's IP address
    inet_ntop(AF_INET, &cli->connfd, cli->ip_addr, INET_ADDRSTRLEN); 
    printf("Connected to client: %s\n", cli->ip_addr);

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // Read message from client
        read(cli->connfd, buff, sizeof(buff));

        // Handle "exit"
        if (strncmp("exit", buff, 4) == 0) {
            printf("Client %s disconnected...\n", cli->ip_addr);
            break;
        }

        // Print message with client IP and get server response
        printf("From %s: %s\t To %s: ", cli->ip_addr, buff, cli->ip_addr); 
        bzero(buff, MAX);
        fgets(buff, MAX, stdin); 

        // Send response to client
        write(cli->connfd, buff, strlen(buff));
    }

    // Close the connection and free memory
    close(cli->connfd);
    free(cli);
    pthread_exit(NULL);
}

int main()
{
    int sockfd, len;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(1); 
    }

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        perror("socket bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(sockfd, 5) != 0) {
        perror("Listen failed");
        exit(1); 
    }

    printf("Server listening on port %d...\n", PORT);

 while (1) {
        struct client_info *cli = malloc(sizeof(*cli)); // Allocate for client_info
        pthread_t thread;

        // Accept connection
        socklen_t len = sizeof(cli);
        cli->connfd = accept(sockfd, (SA*)&cli, &len); 
        if (cli->connfd < 0) {
            perror("server accept failed");
            free(cli); // Free memory if accept fails
            continue; 
        }

        // Get client's IP address
        struct sockaddr_in *client_addr = (struct sockaddr_in *)&cli;
        inet_ntop(AF_INET, &client_addr->sin_addr, cli->ip_addr, INET_ADDRSTRLEN);

        // Create a new thread to handle the client
        if (pthread_create(&thread, NULL, func, (void *)cli) != 0) {
            perror("pthread_create failed");
            close(cli->connfd);
            free(cli);
        }

        // Either join or detach threads based on your memory management strategy.
        //pthread_join(thread, NULL); // Join threads
        pthread_detach(thread); // Detach threads 
    }

    // Close socket (never reached in this version)
    close(sockfd); 
    return 0;
}
