#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "components/headers.h"

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100
#define FILENAME_MAX_LENGTH 256
#define DIRECTORY_PATH "/home/exxo/server/C-Bank/server/data/"

void userDump() {
    char filename[FILENAME_MAX_LENGTH];
    char matrix[MAX_LINES][MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int lineCount;

    char startChar = 'a';
    char endChar = 'z';

    system("clear");

    for (char fileChar = startChar; fileChar <= endChar; fileChar++) {
        // Construct the full file path
        snprintf(filename, FILENAME_MAX_LENGTH, "/home/exxo/server/C-Bank/server/data/%c.txt", fileChar);

        FILE *file = fopen(filename, "r");

        if (file != NULL) {
            lineCount = 0; 

            // Read and store lines in the matrix
            while (fgets(line, sizeof(line), file) != NULL && lineCount < MAX_LINES) {
                line[strcspn(line, "\n")] = 0;
                strcpy(matrix[lineCount], line);
                lineCount++;
            }

            fclose(file);

            // Print contents of the file
            printf("Contents of %s.txt:\n", filename);
            for (int i = 0; i < lineCount; i++) {
                printf("%s\n", matrix[i]);
            }
            printf("\n"); 
        }
    }

    sleep(5);
}

void getUserDetails(const char *email) {
    char filename[FILENAME_MAX_LENGTH];
    snprintf(filename, FILENAME_MAX_LENGTH, "/home/exxo/server/C-Bank/server/data/individuals/%s.txt", email);

    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char matrix[MAX_LINES][MAX_LINE_LENGTH];
        char line[MAX_LINE_LENGTH];
        int lineCount = 0;

        // Read and store user data
        while (fgets(line, sizeof(line), file) != NULL && lineCount < MAX_LINES) {
            line[strcspn(line, "\n")] = 0;
            strcpy(matrix[lineCount], line);
            lineCount++;
        }

        fclose(file);

        // Print user data
        printf("User data for %s:\n", email);
        for (int i = 0; i < lineCount; i++) {
            printf("%s\n", matrix[i]);
        }
    } else {
        printf("User with email %s not found.\n", email);
    }
    sleep(5);
    
}


void removeEmailFromFileHelper(const char *filename, const char *email) {
    char tempFilename[] = "temp.txt";
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen(tempFilename, "w");

    
    if (file == NULL || tempFile == NULL) {
        printf("error opening the files\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int emailFound = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, email) == NULL) {
            fputs(line, tempFile);
        } else {
            emailFound = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (emailFound) {
        remove(filename);
        rename(tempFilename, filename);
        printf("Email '%s' removed successfully from %s.\n", email, filename);
    } else {
        remove(tempFilename);
        printf("Email '%s' not found in %s.\n", email, filename);
    }
}


void delete(const char *email) {
    if (!isalpha(email[0])) {
        printf("Invalid email format: Email must start with a letter.\n");
        return;
    }

    // 1. Remove from letter file (e.g., p.txt)
    char letterFilename[FILENAME_MAX_LENGTH];
    snprintf(letterFilename, FILENAME_MAX_LENGTH, "%s%c.txt", DIRECTORY_PATH, tolower(email[0]));

    removeEmailFromFileHelper(letterFilename, email);

    // 2. Remove individual email file
    char individualFilename[FILENAME_MAX_LENGTH];
    snprintf(individualFilename, FILENAME_MAX_LENGTH, "%s/individuals/%s.txt", DIRECTORY_PATH, email);

    if (remove(individualFilename) == 0) {
        printf("Email file '%s' removed successfully.\n", individualFilename);
    } else {
        printf("Error removing email file '%s'.\n", individualFilename);
    }
}





int main() {
    
    int option = 0;
    bool valid = true;
    char email[100];

    system("clear");

    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            userDump();
            break;
        case 2:
            system("clear");

            printf("Enter email address to lookup: ");
            scanf("%99s", email);

            getUserDetails(email);
            break;
        case 3:
            system("clear");
            printf("Type the user you wish to remove: ");
            scanf("%99s", email);
            delete(email);
            break;
        case 4:
            system("clear");
            break;
        case 5:
            system("clear");
            valid = false;
            break;
        default:
            puts("INVALID INPUT");
            break;
        }
    } while (valid);
    
    



    return 0;
}