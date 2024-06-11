#include <string.h>
#include <stdio.h>

#include "components/headers.h"

int main() {
    char packet[80];
    strcpy(packet, "1tiagoco2008@gmail.com;tigokraft;NotTigo2008!");

    manager(1, packet);

    return 0;
}