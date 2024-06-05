#include <string.h>
#include <stdio.h>

#include "database/components/headers.h"

char* handle(char packet[80]) {
    char* result;

    int value = packet[0] - '0';

    manager(value, packet);
    
    return result;
}