#include "menu.c"
void logo();
void arrowHere(int realPosition, int arrowPosition);
int mainMenu();
int menu2();
struct send;
int moneyMenu(char email[32], float amount, char message[100]);
char* sendMoney();
float depositMenu();

#include "packets.c"
char* create(int option);
char* money(char email[32], float amount, char message[100]);

#include "text.h"

// #include "misc.c"
// void tmpMail(char* email);
// char* getMail();
// void clear();