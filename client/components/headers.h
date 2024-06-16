#include "menu.c"
void logo();
void loading();
void arrowHere(int realPosition, int arrowPosition);
int mainMenu();
int menu2();
struct send;
int moneyMenu(char email[32], float amount, char message[100]);
char* sendMoney();
float depositMenu();
int loanMenu(float amount, int loan);
int loanTypes();

#include "packets.c"
struct user;
char* create(int option);
char* deposit();
char* money(char email[32], float amount, char message[100]);
struct loany;
char* loan();

#include "text.h"

// #include "misc.c"
// void tmpMail(char* email);
// char* getMail();
// void clear();