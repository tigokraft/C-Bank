#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 32
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 16

struct userSave {
    char email [32];
    char username[32];
    char password[16];
};

bool insertion(FILE *file, FILE* individual, char packet[80]) {
    struct userSave u;
    bool eFound = false;
    bool uFound = false;

    int emailSize = 0;
    int userSize = 0;

    char id;

    // Use the file pointer passed in
    FILE *fptr = file;

    if (fptr == NULL) { // Check for valid file pointer
        perror("Error in insertion: Invalid file pointer");
        return false;
    }

    printf("\npacket = %s\n", packet);

    for (int i = 1; i <= strlen(packet); i++) {
        if (packet[i] != ';' && eFound == false) {
            u.email[i-1] = packet[i];
        }
        if (packet[i] == ';' && eFound == false) {
            u.email[i-1] = '\0';
            eFound = true;
            emailSize = strlen(u.email);
        }
        if (packet[i] != ';' && (eFound == true && uFound == false)) {
            u.username[i - emailSize - 2] = packet[i];
        }
        if (packet[i] == ';' && i > emailSize + 1) {
            u.username[i - emailSize - 2] = '\0';
            uFound = true;
            userSize = strlen(u.username);
        }
        if (packet[i] != ';' && (eFound == true && uFound == true)) {
            u.password[i - emailSize - userSize - 3] = packet[i];
        }
        if (i == strlen(packet)) {
            u.password[i - emailSize - userSize - 3] = '\0';
        }
    }

    // print to the screen
    printf("email: %s  |  ", u.email);
    printf("user: %s  |  ", u.username);
    printf("pass: %s\n", u.password);

    // Write to file
    fprintf(fptr, "email: %s\n", u.email);
    fprintf(individual, "user: %s  |  ", u.username);
    fprintf(individual, "pass: %s\n", u.password);

    return true;
}