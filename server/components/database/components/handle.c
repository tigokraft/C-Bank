#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>

// Include header files instead of .c files
#include "insert.c"
#include "lookup.c"
#include "delete.c"

void manager(int option, char packet[80]) {
    char filePath[15];
    char firstChar = tolower(packet[1]);
    snprintf(filePath, sizeof(filePath), "data/%c.txt", firstChar);
    char individualPath[32];
    char email[32];
    

    for (int i = 1; i <= strlen(packet); i++) {
        if (packet[i] != ';') {
            email[i-1] = packet[i];
        }
        if (packet[i] == ';') {
            email[i-1] = '\0';
            i = strlen(packet);
            printf("email = %s  length = %ld\n",email, strlen(individualPath));
        }
    }
    // snprintf(individualPath, sizeof(individualPath), "data/individuals/%s.txt", )

    // Create data directory if it doesn't exist
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0700); // 0700 gives read/write/execute permissions to the owner
    }
    if (stat("data/individuals", &st) == -1) {
        mkdir("data/individuals", 0700); 
    }

    FILE *fptr = NULL; // File pointer declared locally
    FILE *individual = NULL;
    // Option handling (consider a switch statement for clarity)
    if (option == 1) {
        fptr = fopen(filePath, "a+"); 
        if (fptr == NULL) {
            printf("Error opening file");
        }
        individual = fopen(individualPath, "a+");
        insertion(fptr, individual, packet);  // Pass FILE* to insertion
    }
    else if (option == 2) {
        fptr = fopen(filePath, "r");
        if (fptr == NULL) {
            printf("File doesn't exist");
        }
        lookup(fptr, packet);
    }
    
    if (fptr != NULL) {
        fclose(fptr); // Close file after use
    }
}
