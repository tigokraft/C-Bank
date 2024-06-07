#include <string.h>
#include <stdio.h>

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
        user.email = strdup(loginUser());
        user.username = strdup(loginUser());
        user.password = strdup(loginPass());

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(user.username) + strlen(user.password) + strlen(user.email) + 3; // +3 for the null terminator and separators
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "2%s;%s;%s",user.email, user.username, user.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    
    // Remember to free memory for usernames and passwords
    free(user.email);
    free(user.username);
    free(user.password);

    return packet;
}