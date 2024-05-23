#include <winsock2.h>
#include <ws2tcpip.h> // for inet_pton() and related functions
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define MAX 80
#define PORT 8080

void func(SOCKET sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        memset(buff, 0, sizeof(buff)); // Use memset instead of bzero
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0); // Use send instead of write
        memset(buff, 0, sizeof(buff));
        recv(sockfd, buff, sizeof(buff), 0); // Use recv instead of read
        printf("From Server : %s", buff);
        if (strncmp(buff, "exit", 4) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Connect to server
    if (connect(sockfd, (SOCKADDR *)&servaddr, sizeof(servaddr)) != 0) {
        fprintf(stderr, "Connection failed.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    func(sockfd);
    
    // Close socket and clean up Winsock
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
