#include <stdio.h>
#include <windows.h> 
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "text.h"

void logo() {
    SetConsoleOutputCP(CP_UTF8);

    const char *art[] = {
        BGRN," ▄▄·     ▄▄▄▄·  ▄▄▄·  ▐ ▄ ▄ •▄ ",
        "▐█ ▌▪    ▐█ ▀█▪▐█ ▀█ •█▌▐██▌▄▌▪",
        "██ ▄▄ ██ ▐█▀▀█▄▄█▀▀█ ▐█▐▐▌▐▀▀▄·",
        "▐███▌    ██▄▪▐█▐█ ▪▐▌██▐█▌▐█.█▌",
        "·▀▀▀     ·▀▀▀▀  ▀  ▀ ▀▀ █▪·▀  ▀",reset
    };

    int numLines = sizeof(art) / sizeof(art[0]);

    for (int i = 0; i < numLines; i++) {
        printf("%s\n", art[i]);
    }
}

void loading() {
    printf("Logging in...\n{"GRN);
    for (int i = 0; i < 50; i++) {
        printf("═");
        Sleep(20);
    }
    printf(reset"}\n");
    Sleep(500);
}

void information() {
    system("cls");
    printf("This is a bank made in C, open source and for the use of anyone who wishes to test this out or actually base real code out of this (impossible)\n");
    printf("To use this you need to create an account by pressing the first option, or log into an existing account by pressing the second option\n");
    printf("There are some features missing that will soon be added to the program, like notifications and transactions(they exist but are only serverside for now)\n");
    system("pause");
}

// =========================================
//              Arrow Printer
// =========================================
void arrowHere(int realPosition, int arrowPosition) {
    if (realPosition == arrowPosition) {
        printf(" -> ");
    }
    else {
        printf("    ");
    }
}

// =========================================
//            Main screen menu
// =========================================
int mainMenu() {
    int position = 1;
    int keyPressed = 0;

    #define MINMENU 1 
    #define MAXMENU 4

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Sign In \n");
        arrowHere(2,position); printf(" Log In \n");
        arrowHere(3,position); printf(" More Info \n");
        arrowHere(4,position); printf(RED" Exit \n"reset);

        keyPressed = getch();
        fflush(stdin);

        if (keyPressed == 80 && position != MAXMENU) {
            position++;
        }
        else if (keyPressed == 72 && position != MINMENU) {
            position--;
        }
        else if (position == MAXMENU && keyPressed == 80) {
            position = MINMENU;
        }
        else if(position == MINMENU && keyPressed == 72) {
            position = MAXMENU;
        }
        else {
            position = position;
        }

    } while (keyPressed != 13);

    return position;
}

int menu2() {
    int position = 1;
    int keyPressed = 0;

    #define MINMENU2 1 
    #define MAXMENU2 9

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Send Money \n");
        arrowHere(2,position); printf(" Deposit Money \n");
        arrowHere(3,position); printf(" Take a Loan \n");
        arrowHere(4,position); printf(" Balance \n");
        arrowHere(5,position); printf(" Notifications \n");
        arrowHere(6,position); printf(" Get account info \n");
        arrowHere(7,position); printf(" Change password \n");
        arrowHere(8,position); printf(" Account options \n");
        arrowHere(9,position); printf(RED " Log off \n" reset);

        keyPressed = getch();
        fflush(stdin);

        if (keyPressed == 80 && position != MAXMENU2) {
            position++;
        }
        else if (keyPressed == 72 && position != MINMENU2) {
            position--;
        }
        else if (position == MAXMENU2 && keyPressed == 80) {
            position = MINMENU2;
        }
        else if(position == MINMENU2 && keyPressed == 72) {
            position = MAXMENU2;
        }
        else {
            position = position;
        }

    } while (keyPressed != 13);

    return position;
}

struct send {
    char email[32];
    float amount;
    char message[100];
};

int moneyMenu(char email[32], float amount, char message[100]) {
    int position = 1;
    int keyPressed = 0;

    #define MINMONEYMENU 1 
    #define MAXMONEYMENU 5

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Send to: %s \n", email);
        arrowHere(2,position); printf(" Amount: %.2f \n", amount);
        arrowHere(3,position); printf(" Message(optional): %s (NOT WORKING) \n", message);
        arrowHere(4,position); printf(" Send \n");
        arrowHere(5,position); printf(" Cancel \n");

        keyPressed = getch();
        fflush(stdin);

        if (keyPressed == 80 && position != MAXMONEYMENU) {
            position++;
        }
        else if (keyPressed == 72 && position != MINMONEYMENU) {
            position--;
        }
        else if (position == MAXMONEYMENU && keyPressed == 80) {
            position = MINMONEYMENU;
        }
        else if(position == MINMONEYMENU && keyPressed == 72) {
            position = MAXMONEYMENU;
        }
        else {
            position = position;
        }

    } while (keyPressed != 13);

    return position;
}

char* money(char email[32], float amount, char message[100]);

char* sendMoney() {
    char* result;
    int option = 0;

    struct send send;
    send.email[0] = '\0';
    send.amount = 0.0;
    send.message[0] = '\0';

    bool valid = true;
        
    do
    {
        option = moneyMenu(send.email, send.amount, send.message);

        switch (option)
        {
        case 1:
            system("cls");
            fflush(stdin);
            printf("Receiver email: ");
            fgets(send.email, sizeof(send.email), stdin);
            send.email[strcspn(send.email, "\n")] = 0;
            break;
        case 2:
            system("cls");
            fflush(stdin);
            printf("Amount: ");
            if (scanf("%f", &send.amount) == 0) {
                printf("INVALID VALUE\n");
                while(getchar() != '\n');
            }
            break;
        case 3:
            system("cls");
            fflush(stdin);
            printf("Message(max 100 characters): ");
            fgets(send.message, sizeof(send.message), stdin);
            send.message[strcspn(send.message, "\n")] = 0;
            break;
        case 4:
            result = money(send.email, send.amount, send.message);
            valid = false;
            break;
        case 5:
            valid = false;
            result = "false";
            break;
        default:
            break;
        }
    } while (valid);

    return result;
}

float depositMenu() {
    float value = 0;

    system("cls");
    printf("Deposit amount: ");

    if (scanf("%f", &value) == 0) {
        while(getchar() != '\n');
    }
    
    return value;
}

int loanMenu(float amount, int loan) {
    int position = 1;
    int keyPressed = 0;

    #define MINLOANMENU 1 
    #define MAXLOANMENU 4

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Amount: %.2f \n", amount);
        arrowHere(2,position); printf(" Loan type: %.d \n", loan);
        arrowHere(3,position); printf(" Loan \n");
        arrowHere(4,position); printf(" Cancel \n");

        keyPressed = getch();
        fflush(stdin);

        if (keyPressed == 80 && position != MAXLOANMENU) {
            position++;
        }
        else if (keyPressed == 72 && position != MINLOANMENU) {
            position--;
        }
        else if (position == MAXLOANMENU && keyPressed == 80) {
            position = MINLOANMENU;
        }
        else if(position == MINLOANMENU && keyPressed == 72) {
            position = MAXLOANMENU;
        }
        else {
            position = position;
        }

    } while (keyPressed != 13);

    return position;
}

int loanTypes() {
    int position = 1;
    int keyPressed = 0;

    #define MINLOANTYPE 1 
    #define MAXLOANTYPE 7

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" 3 months \n");
        arrowHere(2,position); printf(" 6 months \n");
        arrowHere(3,position); printf(" 9 months \n");
        arrowHere(4,position); printf(" 12 months \n");
        arrowHere(5,position); printf(" 15 months \n");
        arrowHere(6,position); printf(" 18 months \n");
        arrowHere(7,position); printf(" 21 months \n");

        keyPressed = getch();
        fflush(stdin);

        if (keyPressed == 80 && position != MAXLOANTYPE) {
            position++;
        }
        else if (keyPressed == 72 && position != MINLOANTYPE) {
            position--;
        }
        else if (position == MAXLOANTYPE && keyPressed == 80) {
            position = MINLOANTYPE;
        }
        else if(position == MINLOANTYPE && keyPressed == 72) {
            position = MAXLOANTYPE;
        }
        else {
            position = position;
        }

    } while (keyPressed != 13);

    return position;
}