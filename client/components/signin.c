#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

char* signUser() {
    char user[32];
    char* username;

    fflush(stdin);
    printf("Type your name: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    username = strdup(user);
    return username;
}

char* signPass() {
    char pass[16];
    char Rpass[16];
    char* password;
    bool valid = true;

    while (valid) {

        fflush(stdin);
        printf("Type your password: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        fflush(stdin);
        printf("Type your password again to confirm: ");
        fgets(Rpass, sizeof(Rpass), stdin);
        Rpass[strcspn(Rpass, "\n")] = 0;

        if (strcmp(pass, Rpass) == 0) {
            password = strdup(pass);
            valid = false;
        }
        else {
            printf("The passwords dont match!\n");
            Sleep(2);
            system("cls");
        }
    }
    
    return password;
}

char* signEmail() {
    system("cls");
    char* email;
    char text[40];

    bool valid = true;
    
    int size = 0;
    bool ptFound = false;
    bool atFound = false;

    bool firstChecks = false;
    do {
        fflush(stdin);
        printf("Type your email: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0;

        size = strlen(text);

        if (isalpha(text[0]) != 0) {
            firstChecks = true;
        }

        // check if the input is an email
        if (firstChecks) {
            for (int i = 0; i <= size; i++) {
                if (text[i] == '@') {
                    atFound = true;
                }
                if (text[i] == '.' && atFound == true) {
                    ptFound = true;
                }
            }
        }
        
        if (atFound == true && ptFound == true) {
            email = strdup(text);
            valid = false;
        }
        else {
            puts("That is not a valid email!\n");
            Sleep(2);
        }
    } while (valid);    
    return email;
}
