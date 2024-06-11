#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool lookup(FILE* file, FILE* individual, char packet[80]) {
    printf("\npacket = %s\n", packet);

    char string[80];

    fgets(string, sizeof(string), file);

    printf("string = %s\n", string);
}