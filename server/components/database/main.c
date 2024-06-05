#include <string.h>
#include <stdio.h>

#include "components/headers.h"

int main() {
    char packet[80];
    strcpy(packet, "1tiago;test");  

    fflush(stdin);
    printf("Type your username and password:\n");
    fgets(packet, sizeof(packet), stdin);
    packet[strcspn(packet, "\n")] = 0;

    manager(1, packet); // Pass the packet array

    return 0;
}