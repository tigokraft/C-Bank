#include <stdio.h>
#include <windows.h> 

int main() {
    // Set console output code page to UTF-8
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

    return 0;
}
