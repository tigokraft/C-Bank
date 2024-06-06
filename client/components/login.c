#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

char* loginUser() {
    char username[32];
    char* result;

    fflush(stdin);
    printf("Type your username:\n");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    result = strdup(username);
    return result;
}

char* loginPass() {
    char pass[16];
    char* result;
    
    fflush(stdin);
    printf("Type your password:\n");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0; 

    result = strdup(pass);

    return result;
}