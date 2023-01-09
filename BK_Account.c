#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "BK_Accounts.h"

void append(Node** head,Account* newAccount)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	Node* last = *head;

	newNode->mAccount.age = newAccount->age;
	newNode->mAccount.pw = newAccount->pw;
	newNode->mAccount.status = newAccount->status;
	newNode->mAccount.balance = newAccount->balance;
	newNode->mAccount.isGuardian = newAccount->isGuardian;
	newNode->mAccount.bankAccountId = newAccount->bankAccountId;
	strcpy(newNode->mAccount.nationalId, newAccount->nationalId);
	strcpy(newNode->mAccount.guardianNationalId, newAccount->guardianNationalId);
	strcpy(newNode->mAccount.name, newAccount->name);
	strcpy(newNode->mAccount.address, newAccount->address);
	
	newNode->next = NULL;
	if (*head  == NULL)
	{
		*head = newNode;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = newNode;
	return;

}

void display(Node* node)
{
	while (node != NULL)
	{
		printf("********************************\n");
		printf("Name: %s\n",node->mAccount.name);
		printf("National ID: %s\n",node->mAccount.nationalId);
		printf("Address: %s\n",node->mAccount.address);
		printf("Age: %d\n",node->mAccount.age);
		printf("Bank ID %lf\n",node->mAccount.bankAccountId);
		printf("Remaining Balance %lf\n",node->mAccount.balance);
		printf("PW: %d\n",node->mAccount.pw);
		printf("********************************\n");
		node = node->next;
	}
}

Account* createAccount(int *state)
{
	char spaceCount =0,len =0;
	while((getchar()) != '\n');
	static double accounID = 1000000000;
	static Account newAccount;
	newAccount.bankAccountId = accounID;

	printf("Please enter client name: ");
	fgets(newAccount.name,51,stdin);
	int i=0;
	while(newAccount.name[i] != '\0')
	{
		if(newAccount.name[i] == ' ')
		{
			spaceCount++;
		}
		i++;

	}
	if(spaceCount <=2)
	{
		printf("Invalid name\n.Please enter atleast four names");
		*state =0;
		return;
	}

	printf("Please enter client address: ");
	fgets(newAccount.address, 62, stdin);
	len = (strlen(newAccount.address)-1);
	if(len < 10)
	{
		printf("Invalid address\n");
		*state =0;
		return;
	}

	printf("Please enter client age: ");
	scanf("%d", &newAccount.age);
	while((getchar()) != '\n');

	printf("Please enter client national ID: ");
	fgets(newAccount.nationalId, 21, stdin);
	len = (strlen(newAccount.nationalId)-1);
	if(len < 14)
	{
		printf("Invalid national ID\n");
		*state =0;
		return;
	}
	if (newAccount.age < 21)
	{
		printf("Please enter client guardian national ID: ");
		fgets(newAccount.guardianNationalId, 21, stdin);
		newAccount.isGuardian = 'y';
		len = (strlen(newAccount.guardianNationalId)-1);
		if(newAccount.guardianNationalId < 14)
		{
			printf("Invalid guard  national ID");
			*state =0;
			return;
		}

	}
	else
	{
		newAccount.isGuardian = 'n';
	}

	printf("Please enter client balance: ");
	scanf("%lf", &newAccount.balance);
	if(newAccount.balance<0)
	{
		printf("Invalid balance ID");
		*state =0;
		return;
	}

	newAccount.status = ACTIVE;
	accounID++;
	newAccount.pw = passwordGenerator();
	*state =1;
	return &newAccount;
}

void makeTransaction(Node* head,Account* clientAccount)
{
	double otherAccountID =0;
	double transferAmount =0;
	int state =0;
	
	if(clientAccount->status != ACTIVE)
	{
		printf("Account is not active. Please activate account\n");
	}
	else{
		printf("Please enter the bank account ID you want to transfer money to: ");
		scanf("%lf",&otherAccountID);
		Account* recieverAccount = getAccount(head, otherAccountID, &state);
		if(state == 1)
		{
			if(recieverAccount->status != ACTIVE)
			{
				printf("Reciever account is not active\n");
				return;
			}
			else
			{
				printf("Please enter transfer amount: ");
				scanf("%l5f", &transferAmount);
				if(clientAccount->balance < transferAmount)
				{
					printf("Insufficient Balance\n");
				}
				else
				{
					recieverAccount->balance += transferAmount;
					clientAccount->balance -= transferAmount;
					printf("Transaction Successful\n");
					printf("r = %lf  c = %lf\n", recieverAccount->balance,clientAccount->balance);

				}
			}
		}
		else
		{
			printf("Account not found\n");
		}
	}
}

Account* getAccount(Node *head,double recieverId, int* state)
{
	Node* current = head;
	while(current != NULL)
	{
		if(current->mAccount.bankAccountId == recieverId)
		{
			printf("found\n");
			*state = 1;
			printf("state is %d\n", *state);
			return (&current->mAccount);
			
		}
		current = current->next;
	}
	*state = -1;
}

void changeAccountStaus(Account *clientAccount)
{
	printf("Select account state:");
	printf("1- Active\n2- Restricted3- Close");
	char choice;
	scanf("%d",&choice);
	if((choice != ACTIVE) && (choice != RESTRICTED) && (choice!= CLOSED))
	{
		printf("Invlaid input\n");
	}
	else
	{
		clientAccount->status = choice;
		printf("Account status updated\n");
	}
	
}
void getCash(Account *clientAccount)
{
	double withdrawlAmount =0;
	printf("Your current balance: %.2lf\n",clientAccount->balance);
	printf("Please enter withdrawl amount: ");
	scanf("%lf",&withdrawlAmount);
	if((withdrawlAmount <clientAccount->balance) &&(withdrawlAmount>0))
	{
		clientAccount->balance -= withdrawlAmount;
		printf("withdralw successful\n");
		printf("Remaining balance is %.2lf\n",clientAccount->balance);
	}
	else
	{
		printf("Insufficient balance\n");
	}

}
void deposit(Account *clientAccount)
{
	double depositAmount =0;
	printf("Please enter deposit amount: ");
	scanf("%lf",&depositAmount);
	if(deposit >0)
	{
		clientAccount->balance += depositAmount;
		printf("Deposit successful\n");
		printf("Balance is %.2lf\n",clientAccount->balance);
	}
	else
	{
		printf("Invalid deposit amount\n");
	}
}

int passwordGenerator()
{
	return (rand()%(9999-1000+1)+1000);
}



void AppInit(Node **head)
{
	srand(time(NULL));
	Account accountsDB[] = {
		{"Nadeen Mahmoud Elsayed Ali Nadim",
		"22991234561011",
		"3 an address of some place",
		34,
		9999999999,
		'n',
		" ",
		ACTIVE,
		10000,
		1234},

		{"Osman Mohamed Gafar Sonbol",
		"22991234561022",
		"8 happy place",
		50,
		8888888888,
		'n',
		" ",
		ACTIVE,
		7000,
		5678},

		{"fares hossam fatim simba",
		"22991234561033",
		"44 another locatiom",
		13,
		7777777777,
		'y',
		"22991234561022",
		ACTIVE,
		7000,
		9999}
	};
	append(head,&accountsDB[0]);
	append(head,&accountsDB[1]);
	append(head,&accountsDB[2]);


}

void AppStart(Node **head)
{
	char * admin_un = "admin";
	char * admin_pw = "12345";
	char user_pw[6];
	char user_un[6];
	int flag =0 ;
	printf("Welcome to IMT Banking System\n");
	printf("Select one of the following windows:\n1-Admin Window\n2-Client Window\n");
	char userChoice;
	int i =0;
	scanf("%d",&userChoice);
	switch(userChoice)
	{
		case 1:
			printf("Enter Username:\n");
			scanf("%s",&user_un);

			printf("Enter Password:\n");
			scanf("%s",&user_pw);
			
			while(((admin_un[i]) != '\0') && ((admin_pw[i]) != '\0'))
			{
				if((admin_un[i] != user_un[i])||(admin_pw[i] != user_pw[i]))
				{
					printf("Invalid username or password. Please Try again\n");
					flag =-1;
					break;
				}
				else
				{
					flag =255;
				}
				i++;

			}
				if(flag == -1)
				{
					printf("Enter Username: ");
					scanf("%s",&user_un);
					
					printf("Enter Password: ");
					scanf("%s",&user_pw);
					i=0;

				}

			if(flag == 255)
			{
				adminWindow(head);
			}
		break;
		case 2:
		clientWindow(head);
	
		break;
		default:
			printf("Invalid choice. Please Try Again\n");
			break;
	}
}
void adminWindow(Node **head)
{
	while(1)
	{
		printf("Welcome to administrator window:\nPlease select what you want to do\n");
		printf("1-Create new account\n2-Open an existing account\n3-Exit system");
		char userChoice;
		scanf("%d",&userChoice);
		int state;
		switch(userChoice)
		{
			case 1:;
				Account* newacc = createAccount(&state);
				if(state ==1)
				{
					append(head,newacc);
				}
				else
				{
					printf("Could not create account\n");
				}

				break;

			case 2:;
				double accountID = 0;
				
				printf("Enter account ID");
				scanf("%lf", &accountID);
				int x=1;
				Account* clientAcc =getAccount(*head,accountID,&state);
				if(state == 1)
				{
					while(x == 1)
					{
						printf("Please select what you want to do\n");
						printf("1-Make Transaction\n2-Change Accont Status\n3-Get Cash\n4-Add deposit\n5-Back");
						char accountChoice;
						scanf("%d",&accountChoice);
						switch(accountChoice)
						{
							case 1:
							makeTransaction(*head,clientAcc);
							break;
							case 2:
							changeAccountStaus(clientAcc);
							break;
							case 3:
							getCash(clientAcc);
							break;
							case 4:
							deposit(clientAcc);
							break;
							case 5:
							return;
							break;
							default:
							printf("Unrcognized command\n");
							break;



						}
					}
					break;
			}
			case 3:
			return;
			default:
				printf("Unrcognized command\n");
				break;
			
		}
	}
}


void clientWindow(Node **head)
{

	double accountID = 0;
	int accountPw = 0;
	Account* clientAcc;
	while(1)
	{
		printf("Enter bank account ID");
		scanf("%lf", &accountID);
		int state;
		clientAcc= getAccount(*head,accountID,&state);

		if(state == 1)
		{
			printf("Enter your account password:");
			scanf("%d", &accountPw);
			if(clientAcc->pw == accountPw)
			{
				while(1)
				{
					printf("Please select what you want to do\n");
					printf("1-Make Transaction\n2-Change password\n3-Get Cash\n4-Add deposit\n5-Back");
					char accountChoice;
					scanf("%d",&accountChoice);
					switch(accountChoice)
					{
						case 1:
						makeTransaction(*head,clientAcc);
						break;
						case 2:
						changePassword(clientAcc);
						break;
						case 3:
						getCash(clientAcc);
						break;
						case 4:
						deposit(clientAcc);
						break;
						case 5:
						return;
						break;


					}
				}
			}
			else
			{
				printf("%d\n",clientAcc->pw);
			}

		}
		else
		{
			printf("Incorrect Account ID\n");
		}
	}

}

void changePassword(Account *clientAccount)
{
	double newPW;
	printf("Please enter four digit number as your new password: ");
	scanf("%lf",&newPW);
	if(newPW > 999 && newPW <9999)
	{
		clientAccount->pw = newPW;
		printf("Password updated successfuly\n");

	}
	else
	{
		printf("Invalid password\n");
	}
	
}