#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

char* signUser() {
    system("cls");
    char user[32];
    char* username;

    fflush(stdin);
    printf("Type your username:\n");
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
        printf("Type your password:\n");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        fflush(stdin);
        printf("Type your password again to confirm: \n");
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