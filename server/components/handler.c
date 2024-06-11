#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "database/components/headers.h"

char* handle(char* packet) {
    char* result;
    bool valid = false;

    if (packet == NULL) {
        return "Error: Invalid input";
    }

    int value = packet[0] - '0';
    
    valid = manager(value, packet);

    if (valid == true) {
        result = "true";
    }
    else {
        result = "false";
    }

    return result;
}
