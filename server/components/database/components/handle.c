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
            printf("File doesn't exist\n");
        }
        if (individual == NULL) {
            result = "User doesn't exist!\n";
        }
        else {
            valid = lookup(fptr, individual, packet);
            result = validation(valid);
        }
    }
    else if (option == 3) {
        individual = fopen(individualPath, "r+");
        if (individual != NULL) {
            char* balanceStr = getBalance(individual);
            char* delimiterPos = strstr(balanceStr, "1"); 
            if (delimiterPos) {
                *delimiterPos = '\0'; // Replace "1" with null terminator
                balanceStr = delimiterPos + 1; // Move to the start of the value
            }

            float balance = convertToFloat(balanceStr);
            float amount = convertToFloat(findAmount(packet, email));
            float count = 0;
            float add = 0;
            char recEmail[32];

            size_t packetSize = strlen(packet);
            size_t email2 = strlen(email) + strlen(findAmount(packet, email)) + 3;

            for (int i = email2; i <= packetSize; i++) {
                if (packet[i] != ';') {
                    recEmail[i-email2] = packet[i];
                }
                if (packet[i] == '\0') {
                    recEmail[i-email2] = '\0';
                    i = strlen(packet);
                    printf("receiver email = %s\n", recEmail);
                }
            }

            char recPath[64];
            snprintf(recPath, sizeof(recPath), "data/individuals/%s.txt", recEmail);
            
            if (getUser(recEmail)) {
                printf("balance = %.2f\n", balance);

                if (amount > balance) {
                    result = strdup("You don't have enought money!");
                }
                else {
                    count = balance - amount;
                    printf("count = %.2f\n", count);

                    fclose(individual);
                    individual = NULL;
                    changeBal(individualPath, count);

                    FILE* rec = fopen(recPath, "r");
                    char* recBalance = getBalance(rec);
                    char* delimiterPos = strstr(recBalance, "1"); 
                    if (delimiterPos) {
                        *delimiterPos = '\0'; // Replace "1" with null terminator
                        recBalance = delimiterPos + 1; // Move to the start of the value
                    }
                    fclose(rec);

                    float recBal = convertToFloat(recBalance);
                    printf("rec Bal: %.2f\n", recBal);
                    float finalBal = recBal += amount;

                    changeBal(recPath, finalBal);
                    result = strdup("true");

                    
                }
            }
            else {
                return strdup("user not found");
            }

        }
    }
    else if (option == 4) {
        individual = fopen(individualPath, "r+");
        if (individual != NULL) {
            char* balanceStr = getBalance(individual);
            char* delimiterPos = strstr(balanceStr, "1"); 
            if (delimiterPos) {
                *delimiterPos = '\0'; // Replace "1" with null terminator
                balanceStr = delimiterPos + 1; // Move to the start of the value
            }

            float balance = convertToFloat(balanceStr);
            float amount = convertToFloat(findAmount(packet, email));

            float final = balance + amount;

            fclose(individual);
            individual = NULL;
            changeBal(individualPath, final);

            result = strdup("true");
        }
    }
    else if (option == 5) {
        individual = fopen(individualPath, "r+");
        if (individual != NULL) {
            char* balanceStr = getBalance(individual);
            char* delimiterPos = strstr(balanceStr, "1"); 
            if (delimiterPos) {
                *delimiterPos = '\0'; // Replace "1" with null terminator
                balanceStr = delimiterPos + 1; // Move to the start of the value
            }

            float balance = convertToFloat(balanceStr);
            float amount = convertToFloat(findAmount(packet, email));

            float final = balance + amount;

            fclose(individual);
            individual = NULL;
            changeBal(individualPath, final);

            result = strdup("true");
        }
    }
    else if (option == 6) {
        individual = fopen(individualPath, "r");
        if (individual == NULL) {
            printf("unkown balance\n");
        }
        else {
            printf("getting balance from %s\n", email);
            result = getBalance(individual);
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

void sendNotifications() {

}