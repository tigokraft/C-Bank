#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

char* loginPass() {
    char pass[16];
    char* result;
    
    fflush(stdin);
    printf("Type your password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0; 

    result = strdup(pass);

    return result;
}

char* loginEmail() {
    system("cls");
    char* email;
    char text[40];

    fflush(stdin);
    printf("Type your email: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    email = strdup(text);

    return email;
}