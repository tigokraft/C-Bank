#include <string.h>
#include <stdio.h>

void tmpMail(char* email) {
    FILE* fptr = fopen("tmp.txt", "w");

    if (fptr == NULL) {
        printf("Error opening the file\n");
        exit(1);
    } 

    fprintf(fptr, "%s\n", email);

    fclose(fptr);
}

char* getMail() {
    char email[32];
    char* result;
    FILE* fptr = fopen("tmp.txt", "r");

    fgets(email, sizeof(email), fptr);
    email[strcspn(email, "\n")] = 0; 
    fclose(fptr);

    result = strdup(email);
    return result;
}

void clear() {
    remove("tmp.txt");
}

int floatSize(float value) {
    int size = 0;
    char buffer[20];

    size = snprintf(buffer, sizeof(buffer), "%.2f", value);
    
    return size;
}

void saveBal(char* packet) {
    FILE* fptr = fopen("tmp.txt", "a+");

    char* result;
    char* word = "1";

    char* final = NULL;
    size_t size;

    char* packetdup = packet;
    size = strlen(packet);

    result = strstr(packet, word);

    if (result != NULL) {
        size_t lineLen = strlen(packetdup);
        size_t wordLen = strlen(word);

        // Shift characters to overwrite the found word
        memmove(result, result + wordLen, lineLen - (result - packetdup) - wordLen + 1); 
        // Ensure null-terminator is in place
        packetdup[lineLen - wordLen] = '\0';
    }
    snprintf(final, size, "%.2f", packetdup);
    printf("final = %s\n", final);
    system("pause");
    fprintf(fptr, "%s\n", final);
    fclose(fptr);
}

float getBal() {
    float balance = 0;

    FILE* fptr = fopen("tmp.txt", "r");
    char line[40];

    for (int i = 0; i < 1; i++) {
        fgets(line, sizeof(line), fptr);
    }

    fscanf(fptr, "%f", &balance);

    fclose(fptr);

    return balance;
}