#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <io.h>
#include <locale.h>

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
    FILE* inputFile = fopen("tmp.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    char line2[100];
    for (int i = 0; i < 2; i++) {
        fgets(line2, sizeof(line2), inputFile);
        if (i == 0){
            if (strstr(line2, "line to erase") == NULL) {
                fputs(line2, outputFile);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    // replace input.txt with output.txt
    remove("tmp.txt");
    rename("output.txt", "tmp.txt");

    FILE* fptr = fopen("tmp.txt", "r+");

    char* word = "1";
    char* final = NULL;
    size_t size;
    char* packetdup = packet;
    size = strlen(packet) + 2;

    
    char line[100];
    size_t line_no = 0;
    while (fgets(line, sizeof(line), fptr)) {
        line_no++;
        if (line_no == 2) {
            fseek(fptr, -strlen(line), SEEK_CUR); // move the pointer back to the start of the line
            break;
        }
    }

    char* result = strstr(packet, word);

    if (result != NULL) {
        size_t lineLen = strlen(packetdup);
        size_t wordLen = strlen(word);

        // Shift characters to overwrite the found word
        memmove(result, result + wordLen, lineLen - (result - packetdup) - wordLen + 1); 
        // Ensure null-terminator is in place
        packetdup[lineLen - wordLen] = '\0';
    }
    final = (char*)malloc(size);


    snprintf(final, size, "%s", packetdup);

    fprintf(fptr, "%s\n", final);
    fclose(fptr);
}

char* getBal() {
    float balance = 0;

    FILE* fptr = fopen("tmp.txt", "r");
    char line[100];

    for (int i = 0; i < 2; i++) {
        fgets(line, sizeof(line), fptr);
    }

    fclose(fptr);

    return strdup(line);
}