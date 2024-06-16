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
    fclose(fptr);

    result = strdup(email);
    return result;
}

void clear() {
    remove("tmp.txt");
}