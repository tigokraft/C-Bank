#include <string.h>
#include <stdio.h>
#include <windows.h>

#include "signin.c"
#include "login.c"
#include "misc.c"

void tmpMail(char* email);

struct user {
    char* email;
    char* username;
    char* password;
};

char* create(int option) {
    struct user user;
    char* packet = NULL;
    size_t packetSize = 0; // To track the actual size of the packet

    float amount = 0;

    if (option == 1) { // sign in
        user.email = strdup(signEmail());
        user.username = strdup(signUser());
        user.password = strdup(signPass());
            
        tmpMail(user.email);

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(user.username) + strlen(user.password)  + strlen(user.email) + 3; // +3 for the null terminator and separators
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "1%s;%s;%s",user.email, user.username, user.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    else if (option == 2) {
        user.email = strdup(loginEmail());
        user.password = strdup(loginPass());

        tmpMail(user.email);

        // Calculate the required size for the packet
        packetSize = strlen("1") + strlen(user.password) + strlen(user.email) + 2; // +2 for the null terminator and separators
        
        // Dynamically allocate memory for the packet
        packet = (char*)malloc(packetSize);

        if (packet != NULL) { // Check if allocation was successful
            snprintf(packet, packetSize, "2%s;%s",user.email, user.password);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }

    
    // Remember to free memory for usernames and passwords
    free(user.email);
    free(user.username);
    free(user.password);

    return packet;
}


char* deposit() {
    char* packet = NULL;
    float value = depositMenu();
    char* email = strdup(getMail());

    size_t packetSize;
    
    printf("email: %s\n", email);
    printf("value: %.2f\n", value);

    packetSize = strlen(email) + floatSize(value) + 4;
    packet = (char*)malloc(packetSize);

    if (packet != NULL) {
        snprintf(packet, packetSize, "4%s;%.2f", email, value);
    }
    
    printf("packet = %s\n", packet);

    system("pause");

    return packet;
}

char* money(char email[32], float amount, char message[100]) {
    char* packet = NULL;
    size_t packetSize;
    char* userEmail = getMail();

    printf("email %s\namount %.2f\nmessage %s\n", email, amount, message);

    if (message[0] == '\0') {
        packetSize = strlen(userEmail) + strlen(email) + floatSize(amount) + 4;
        packet = (char*)malloc(packetSize);

        if (packet != NULL) {
            snprintf(packet, packetSize, "3%s;%.2f;%s",userEmail, amount, email);
        }
    }
    else {
        printf("message = %ld\namount = %d\n", strlen(message), floatSize(amount));
        packetSize = strlen(userEmail) + strlen(email) + floatSize(amount) + strlen(message) + 5 + 3 + 2;
        packet = (char*)malloc(packetSize);
        printf("packet = %u\n", packetSize);

        if (packet != NULL) {
            snprintf(packet, packetSize, "3%s;%.2f;%s;%s",userEmail, amount, email, message);
        }
    }
    system("pause");

    return packet;
}

struct loany {
    float amount;
    int loan;
};

char* loan() {
    char* packet = NULL;
    size_t packetSize;
    bool valid = true;
    bool sent = false;

    char* email = getMail();

    int option = 0;

    struct loany l;

    l.amount = 0.00;
    l.loan = 0;

    do
    {
        system("cls");
        option = loanMenu(l.amount, l.loan);

        if (option == 1) {
            system("cls");
            fflush(stdin);
            printf("Amount: ");
            if (scanf("%f", &l.amount) == 0) {
                printf("INVALID VALUE\n");
                while(getchar() != '\n');
            }
        }
        else if (option == 2) {
            system("cls");
            l.loan = loanTypes();
        }
        else if (option == 3) {
            sent = true;
            valid = false;
        }
        else if (option == 4) {
            valid = false;
        }
    } while (valid);
    

    if (sent) {
        packetSize = strlen(email) + floatSize(l.amount) + 6;
        packet = (char*)malloc(packetSize);

        if (packet != NULL) {
            snprintf(packet, packetSize, "5%s;%.2f;%d", email, l.amount, l.loan);
        }
    }

    return packet;
}

char* balance() {
    char* packet = NULL;
    size_t packetSize;

    char* email = getMail();

    packetSize = strlen(email) + 3;
    packet = (char*)malloc(packetSize);

    if (packet != NULL) {
        snprintf(packet, packetSize, "6%s", email);
    }
    
    return packet;
}
