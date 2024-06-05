#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 16

struct userSave {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void insertion(FILE *file, char packet[80]) {
    struct userSave u;
    int divider = 0;

    // Use the file pointer passed in
    FILE *fptr = file;

    if (fptr == NULL) { // Check for valid file pointer
        perror("Error in insertion: Invalid file pointer");
        return;
    }

    // Find the divider (';') in the packet
    for (int i = 1; i < strlen(packet); i++) {
        if (packet[i] == ';') {
            divider = i;
            break; // Exit loop once divider is found
        }
    }
	
    // Find the username
    for (int i = 1; i <= divider && i < MAX_USERNAME_LENGTH; i++) { 
        u.username[i - 1] = packet[i];
    }
    u.username[divider] = '\0'; // Null-terminate the username

    // size of the username (used to find 0 position in i)
    int userSize = strlen(u.username) + 1; // Add 1 to include the null terminator

    // Find the password
    for (int i = divider + 1; i < strlen(packet) && (i - userSize) < MAX_PASSWORD_LENGTH; i++) { 
        u.password[i - userSize] = packet[i];
    }
    u.password[strlen(packet) - userSize] = '\0'; // Null-terminate the password

    fprintf(fptr, "user: %s | ", u.username);
    fprintf(fptr, "pass: %s\n", u.password);
}
