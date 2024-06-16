#include <string.h>
#include <stdio.h>
#include <stdbool.h>

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



// char* name(FILE* individual) {
//     char* result;
    
    

//     return ;
// }