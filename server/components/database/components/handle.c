#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// Include header files instead of .c files
#include "insert.c"
#include "lookup.c"
#include "delete.c"

char* validation(bool check) {
    char* result;

    if (check) {
        result = "true";
    }
    else {
        result = "false";
    }

    return result;
}

char* manager(int option, char packet[80]) {
    bool valid = false;

    char filePath[15];
    char firstChar = tolower(packet[1]);
    snprintf(filePath, sizeof(filePath), "data/%c.txt", firstChar);
    char individualPath[64];
    char email[32];

    char* result = "false";
    
    
    for (int i = 1; i <= strlen(packet); i++) {
        if (packet[i] != ';') {
            email[i-1] = packet[i];
        }
        if (packet[i] == ';') {
            email[i-1] = '\0';
            i = strlen(packet);
            printf("email = %s  length = %ld\n",email, strlen(email));
        }
    }
    snprintf(individualPath, sizeof(individualPath), "data/individuals/%s.txt", email);


    // Create data directory if it doesn't exist
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0700);
    }
    if (stat("data/individuals", &st) == -1) {
        mkdir("data/individuals", 0700); 
    }


    FILE *fptr = NULL; // File pointer declared locally
    FILE *individual = NULL;


    // Option handling (consider a switch statement for clarity)
    if (option == 1) {
        if (access(individualPath, F_OK) == 0) {
            printf("User already exists\n");
            result = strdup("User already exists");
        }
        fptr = fopen(filePath, "a+");
        if (fptr == NULL) {
            printf("Error opening file\n");
        }
        else {
            individual = fopen(individualPath, "w");
            if (individual == NULL) {
                printf("error creating user\n");
            }

            valid = insertion(fptr, individual, packet);
            result = validation(valid);
        }

    }
    else if (option == 2) {
        fptr = fopen(filePath, "r");
        individual = fopen(individualPath, "r");
        if (fptr == NULL) {
            printf("File doesn't exist");
        }
        if (individual == NULL) {
            result = "User doesn't exist!\n";
        }
        else {
            valid = lookup(fptr, individual, packet);
            result = validation(valid);
        }
    }
    

    if (fptr != NULL) {
        fclose(fptr);
    }
    if (individual != NULL) {
        fclose(individual);
    }

    return result;
}
