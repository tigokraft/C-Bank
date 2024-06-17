#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void bzero(char *buffer, int size) {
    memset(buffer, '\0', size);
}

#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define MAX 200
#define PORT 2000

#include "components/headers.h"

bool func(SOCKET sockfd, char* packet)
{
    const char* messageToSend = strdup(packet); // The string to send
    int messageLen = strlen(messageToSend); // Calculate string length

    // Send the message
    send(sockfd, messageToSend, messageLen, 0); 

    free(packet);

    // Receive and print response (optional, depends on your server logic)
    char buff[MAX];
    memset(buff, 0, sizeof(buff));
    recv(sockfd, buff, sizeof(buff), 0);
    packet = strdup(buff);

    if (buff[0] == '1') {
        saveBal(packet);
        return true;
    }

    bzero(buff, MAX);

    if (strcmp(packet, "true") == 0) {
        return true;
    }
    else {
        Sleep(2000);
        return false;
    }
}


int main()
{
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    int option = 0;
    int option2 = 0;
    bool valid = true;
    bool session = false;
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
    servaddr.sin_addr.s_addr = inet_addr("148.71.24.137");  
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
            if (func(sockfd, packet)) {
                loading();
                session = true;
                packet = strdup(balance());
                func(sockfd, packet);

                do
                {
                    option2 = menu2();
                    switch (option2)
                    {
                    case 1:
                        packet = strdup(sendMoney());
                        func(sockfd, packet);
                        break;
                    case 2: 
                        packet = strdup(deposit());
                        func(sockfd, packet);
                        break;
                    case 3:
                        packet = strdup(loan());
                        func(sockfd, packet);
                        break;
                    case 4:
                        packet = strdup(balance());
                        if (func(sockfd, packet)) {
                            system("pause");

                            system("cls");
                            printf("Balance: %s\n", getBal()); 
                        }
                        break;
                    case 9:
                        clear();
                        session = false;
                    default:
                        break;
                    }
                } while (session);               
            }
            break;
        case 2:
            packet = strdup(create(2));
            if (func(sockfd, packet)) {
                loading();
                session = true;
                packet = strdup(balance());
                func(sockfd, packet);

                do
                {
                    option2 = menu2();
                    switch (option2)
                    {
                    case 1:
                        packet = strdup(sendMoney());
                        if (strcmp(packet, "false") != 0) {
                            func(sockfd, packet);
                        }
                        break;
                    case 2:
                        packet = strdup(deposit());
                        func(sockfd, packet);
                        break;
                    case 3:
                        packet = strdup(loan());
                        if (packet != NULL) {
                            func(sockfd, packet);
                        }
                        break;
                    case 4:
                        packet = strdup(balance());
                        if (func(sockfd, packet)) {

                            system("cls");
                            printf("Balance: %s\n", getBal()); 
                            system("pause");
                        }
                        break;
                    case 9:
                        clear();
                        session = false;
                    default:
                        break;
                    }
                } while (session);               
            }
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