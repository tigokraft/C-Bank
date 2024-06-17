#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h> 


bool lookup(FILE* file, FILE* individual, char packet[80]) {
    char email[32];
    char pass[32];
    int emailSize = 0;
    char tmp[32];
    char tmpmail[32];
    int lineCount = 0;


    bool found = false;

    size_t passLen;
    size_t wordLen;

    char *word = "pass: ";
    char *result;


    for (int i = 1; i <= strlen(packet); i++) {
        if (packet[i] != ';') {
            email[i-1] = packet[i];
        }
        if (packet[i] == ';') {
            email[i-1] = '\0';
            emailSize = strlen(email);
        }
        if (emailSize > 0) {
            if(packet[i] != ';') {
                tmp[i - emailSize - 2] = packet[i];
            }
        }
    }

    while (!found) {
        fgets(tmpmail, sizeof(tmpmail), file);
        tmpmail[strcspn(tmpmail, "\n")] = 0;

        if (strcmp(tmpmail, email) == 0) {
            found = true;
        }
    }

    if (found) {
        while (fgets(pass, sizeof(pass), individual) != NULL) {
            lineCount++;
            if (lineCount == 2) {
                printf("%s\n", pass); // Print the second line
                break;
            }
        }

        result = strstr(pass, word);

        if (result != NULL) {
            size_t passLen = strlen(pass);
            size_t wordLen = strlen(word);

            // Shift characters to overwrite the found word
            memmove(result, result + wordLen, passLen - (result - pass) - wordLen + 1); 
            // Ensure null-terminator is in place
            pass[passLen - wordLen] = '\0';
        }

        pass[strcspn(pass, "\n")] = 0;
        
        printf("tmp = %s\npass = %s\n", tmp, pass);

        if(strcmp(tmp, pass) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

char* getBalance(FILE* fptr) {
    char line[100];
    char* result;

    for(int i = 0; i < 3; i++) {
        fgets(line, sizeof(line), fptr);
    }
    line[strcspn(line, "\n")] = 0; 
    char* word = "balance: ";

    result = strstr(line, word);

    if (result != NULL) {
        size_t lineLen = strlen(line);
        size_t wordLen = strlen(word);

        // Shift characters to overwrite the found word
        memmove(result, result + wordLen, lineLen - (result - line) - wordLen + 1); 
        // Ensure null-terminator is in place
        line[lineLen - wordLen] = '\0';
    }

    size_t packetSize = strlen(line) + 2;
    char* packet = (char*)malloc(packetSize);
    snprintf(packet, packetSize, "1%s", line);

    return packet;
}

float convertToFloat(char* string) {
    char* endptr; 
    float result = (float) strtod(string, &endptr);
    
    return result;
}

char* findAmount(char* packet, char* email){
    size_t packetSize = strlen(packet);
    size_t emailSize = strlen(email) + 2;

    char result[20];

    for (int i = emailSize; i <= packetSize; i++) {
        if (packet[i] != ';') {
            result[i - emailSize] = packet[i];
        }
        if (packet[i] == ';') {
            result[i - emailSize] = '\0';
            i = packetSize;
        }
    }

    printf("amount = %s | lenght = %ld\n", result, strlen(result));

    return strdup(result);
}

bool getUser(char email[32]) {
    char ch = email[0];
    char check[11];
    char line[100];

    bool found = false;

    snprintf(check, sizeof(check), "data/%c.txt", ch);

    FILE* fptr = fopen(check, "r");

    if (fptr == NULL) {
        // Handle file not found (e.g., return false, log an error)
        fprintf(stderr, "Error opening file %s: %s\n", check, strerror(errno));
        return false; 
    }

    
    while(fgets(line, sizeof(line), fptr) != NULL && !found) {
        line[strcspn(line, "\n")] = 0; 
        if (strcmp(line, email) == 0) {
            found = true;
        }
    }

    fclose(fptr);

    return found;
}


// char* name(FILE* individual) {
//     char* result;
    
    

//     return ;
// }