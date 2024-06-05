#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>

// Include header files instead of .c files
#include "insert.c"
#include "lookup.c"
#include "delete.c"

// No global file pointer
//FILE *fptr; 

char* manager(int option, char packet[80]) {
    char filePath[15];
    char firstChar = tolower(packet[1]);
    snprintf(filePath, sizeof(filePath), "data/%c.txt", firstChar);

    // Create data directory if it doesn't exist
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0700); // 0700 gives read/write/execute permissions to the owner
    }

    FILE *fptr = NULL; // File pointer declared locally

    // Option handling (consider a switch statement for clarity)
    if (option == 1) {
        fptr = fopen(filePath, "a"); 
        if (fptr == NULL) {
            return "Error opening file"; 
        }
        insertion(fptr, packet);  // Pass FILE* to insertion
    }
    
    if (fptr != NULL) {
        fclose(fptr); // Close file after use
    }

    return "working"; // Default success message
}
