#include <stdio.h>
#include <windows.h> 
#include <conio.h>

void logo() {
    SetConsoleOutputCP(CP_UTF8);

    const char *art[] = {
        " ▄▄·     ▄▄▄▄·  ▄▄▄·  ▐ ▄ ▄ •▄ ",
        "▐█ ▌▪    ▐█ ▀█▪▐█ ▀█ •█▌▐██▌▄▌▪",
        "██ ▄▄ ██ ▐█▀▀█▄▄█▀▀█ ▐█▐▐▌▐▀▀▄·",
        "▐███▌    ██▄▪▐█▐█ ▪▐▌██▐█▌▐█.█▌",
        "·▀▀▀     ·▀▀▀▀  ▀  ▀ ▀▀ █▪·▀  ▀"
    };

    int numLines = sizeof(art) / sizeof(art[0]);

    for (int i = 0; i < numLines; i++) {
        printf("%s\n", art[i]);
    }
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
        arrowHere(4,position); printf(" Exit \n");

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
    #define MAXMENU2 8

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Send Money \n");
        arrowHere(2,position); printf(" Balance \n");
        arrowHere(3,position); printf(" Take a Loan \n");
        arrowHere(4,position); printf(" Notifications \n");
        arrowHere(5,position); printf(" Get account info \n");
        arrowHere(6,position); printf(" Change password \n");
        arrowHere(7,position); printf(" Account options \n");
        arrowHere(8,position); printf(" Log off \n");

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
    char message[50]
};

int moneyMenu() {
    int position = 1;
    int keyPressed = 0;

    struct send s;

    #define MINMENU2 1 
    #define MAXMENU2 5

    do
    {
        system("cls");

        logo();

        arrowHere(1,position); printf(" Send to: %s \n", s.email);
        arrowHere(2,position); printf(" Amount: %.2f \n", s.amount);
        arrowHere(3,position); printf(" Message(optional): %s \n", s.message);
        arrowHere(4,position); printf(" Send \n");
        arrowHere(5,position); printf(" Cancel \n");

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

char* sendMoney() {
    char* result;
    int option = 0;

    struct send send;
    
    bool valid = true;
        
    do
    {
        option = sendMenu();

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
            scanf("%f", &send.amount);
            break;
        case 3:
            system("cls");
            fflush(stdin);
            printf("Message: ");
            fgets(send.message, sizeof(send.message), stdin);
            send.message[strcspn(send.message, "\n")] = 0;
            break;
        default:
            break;
        }
    } while (valid);
    
    

    return result;
}