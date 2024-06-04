#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define MAX 80
#define PORT 8080

#include "components/headers.h"

void func(SOCKET sockfd, char* packet)
{
    const char* messageToSend = strdup(packet); // The string to send
    int messageLen = strlen(messageToSend); // Calculate string length

    // Send the message
    send(sockfd, messageToSend, messageLen, 0); 

    // Receive and print response (optional, depends on your server logic)
    char buff[MAX];
    memset(buff, 0, sizeof(buff));
    recv(sockfd, buff, sizeof(buff), 0);
    printf("From Server: %s", buff); 
}


int main()
{
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    int option = 0;
    bool valid = true;
    char* packet; 


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

    // convert the ip to usable data
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.123");  
    if (servaddr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "Invalid address.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // server connection
    if (connect(sockfd, (SOCKADDR*)&servaddr, sizeof(servaddr)) != 0) {
        fprintf(stderr, "Connection failed.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    
    do
    {   
        option = mainMenu();
        switch (option)
        {
        case 1:
            packet = strdup(create(1));
            printf("%s\n", packet);
            func(sockfd, packet);
            break;
        case 2:
            packet = strdup(create(2));
            func(sockfd, packet);
            break;
        case 3:

            break;
        case 4:
            valid = false;
            system("cls");
            break;
        default:
            break;
        }
    } while (valid);


    
    // Close socket and clean up Winsock (no changes)
    closesocket(sockfd);
    WSACleanup();
    return 0;
}