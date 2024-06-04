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