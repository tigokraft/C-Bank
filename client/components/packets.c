#include <string.h>
#include <stdio.h>
#include <windows.h>

#include "signin.c"
#include "login.c"

struct user {
    char* email;
    char* username;
    char* password;
};

char* create(int option) {
    struct user user;
    char* packet = NULL;
    size_t packetSize = 0; // To track the actual size of the packet

    if (option == 1) { // sign in
        user.email = strdup(signEmail());
        user.username = strdup(signUser());
        user.password = strdup(signPass());

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(user.username) + strlen(user.password)  + strlen(user.email) + 3; // +3 for the null terminator and separators
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "1%s;%s;%s",user.email, user.username, user.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    else if (option == 2) {
        user.email = strdup(loginEmail());
        user.password = strdup(loginPass());

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(user.password) + strlen(user.email) + 2; // +2 for the null terminator and separators
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "2%s;%s",user.email, user.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    else if (option == 3) {
        
    }
    
    // Remember to free memory for usernames and passwords
    free(user.email);
    free(user.username);
    free(user.password);

    return packet;
}

char* money(char email[32], float amount, char message[100]) {
    char* packet;
    size_t packetSize;

    struct send s;

    printf("email %s\namount %.2f\nmessage %s\n", email, amount, message);

    if (message[0] == '\0') {
        packetSize = strlen(email) + 8;
        packet = (char*)malloc(packetSize);

        if (packet != NULL) {
            snprintf(packet, packetSize, "3%s;%.2f",email, amount);
        }
    }
    else {
        printf("message = %ld\namount = %d", strlen(message), sizeof(amount));
        packetSize = strlen(email) + sizeof(amount)+ strlen(message) + 5 ;
        packet = (char*)malloc(packetSize);
        printf("packet = %u\n", packetSize);

        if (packet != NULL) {
            snprintf(packet, packetSize, "3%s;%.2f;%s",email, amount, message);
        }
    }
    system("pause");

    return packet;
}