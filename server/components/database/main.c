#include <string.h>
#include <stdio.h>

#include "components/headers.h"

int main() {
    char packet[80];
    strcpy(packet, "2tiagoco2008@gmail.com;tigokraft;NotTigo2008!");

    manager(2, packet);

    return 0;
}