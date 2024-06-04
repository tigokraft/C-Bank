#include <string.h>

#include "signin.c"

struct user {
    char* username;
    char* password;
};

char* create(int option) {
    struct user u;
    char* packet = NULL;
    size_t packetSize = 0; // To track the actual size of the packet

    if (option == 1) { // sign in
        u.username = strdup(signUser());
        u.password = strdup(signPass());

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(u.username) + strlen(u.password) + strlen(";") + 1; // +1 for the null terminator
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "1%s;%s", u.username, u.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    
    // Remember to free memory for usernames and passwords
    free(u.username);
    free(u.password);

    return packet;
}