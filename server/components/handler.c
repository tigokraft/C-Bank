#include <string.h>
#include <stdio.h>

#include "database/components/headers.h"

char* handle(char* packet) {
    char* result = "worked";

    if (packet == NULL) {
        return "Error: Invalid input"; // Example
    }

    int value = packet[0] - '0';
    printf("%d\n", value);

    manager(value, packet);
    
    return result;
}
