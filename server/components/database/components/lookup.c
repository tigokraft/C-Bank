#include <string.h>
#include <stdio.h>

char* lookup(FILE* file, char packet[80]) {
    printf("\npacket = %s\n", packet);

    char string[80];

    fgets(string, sizeof(string), file);

    printf("string = %s\n", string);
}