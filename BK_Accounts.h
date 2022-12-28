#ifndef BK_ACCOUNTS_H
#define BK_ACCOUNTS_H


typedef enum
{
	ACTIVE = 1,
	RESTRICTED,
	CLOSED
}accountStatus;

typedef struct
{
	char name[51];
	char nationalId[21];
	char address[62];
	int age;
	double bankAccountId;
	char isGuardian;
	char guardianNationalId[21];
	accountStatus status;
	double balance;
	int pw;

}Account;

typedef struct
{
	Account mAccount;
	struct Node* next;
}Node;


void append(Node** head,Account* newAccount);
void display(Node* node);

Account* createAccount(int *state);

Account* getAccount(Node *head,double recieverId, int* state);
void makeTransaction(Node* head,Account* clientAccount);

void changeAccountStaus(Account *clientAccount);
void getCash(Account *clientAccount);
void deposit(Account *clientAccount);
void changePassword(Account *clientAccount);

int passwordGenerator();

void AppStart(Node **head);
void AppInit(Node **head);

void adminWindow(Node **head);
void clientWindow(Node **head);



#endif