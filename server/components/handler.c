#include <string.h>
#include <stdio.h>

#include "database/components/headers.h"

char* handle(char* packet) {
    char* result;

    if (packet == NULL) {
        return "Error: Invalid input";
    }

    int value = packet[0] - '0';
    
    manager(value, packet);
    
    return result;
}
