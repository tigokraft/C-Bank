#include <stdio.h>

int menu() {
    int option = 0;

    printf(" ====================================\n");
    printf("|                                    |\n");
    printf("|              DATABASE              |\n");
    printf("|                                    |\n");
    printf(" ====================================\n\n");
    
    printf
    (
        "1 -> list all of the users\n"
        "2 -> lookup a user\n"
        "3 -> remove a user\n"
        "4 -> clear\n"
        "5 -> exit\n"
    );

    scanf("%d", &option);

    return option;
}