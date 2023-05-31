#include <stdio.h>
#include <stdlib.h>

int acnoInit = 100;

typedef struct Account
{
    char name[100];
    int acno;
    char address[100];
    double balance;
} Account;

Account *accounts[1000];
int acindex = 0;

void executeGitCommand(const char *command)
{
    char gitCommand[100];
    snprintf(gitCommand, sizeof(gitCommand), "git %s", command);
    int result = system(gitCommand);
    if (result == -1)
    {
        printf("Failed to execute Git command.\n");
    }
}

Account *createAccount()
{
    Account *account = (Account *)malloc(sizeof(Account));
    printf("Enter your name:\n");
    scanf("%s", &account->name);
    printf("Enter your address:\n");
    scanf("%s", &account->address);
    printf("Enter the amount you want to deposit initially(>= 500):\n");
    scanf("%lf", &account->balance);
    account->acno = acnoInit++;

    accounts[acindex++] = account;

    printf("Account Details:\n");
    printf("Name: %s\n", account->name);
    printf("Address: %s\n", account->address);
    printf("Account number: %d\n", account->acno);
    printf("Balance: %lf\n", account->balance);

    executeGitCommand("add .");
    executeGitCommand("commit -m \"New Account Created\"");
}

void deposit()
{
    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);
    int i;
    for (i = 0; i < 1000; i++)
    {
        // printf("Hi");
        if (accounts[i]->acno == acno)
        {
            double b;
            printf("Enter the amount you want to deposit:\n");
            scanf("%lf", &b);
            accounts[i]->balance += b;
            printf("Amount deposited\nAvailable balance: %lf", accounts[i]->balance);
            executeGitCommand("add .");
            executeGitCommand("commit -m \"Balance deposited\"");
            return;
        }
    }
    printf("Account not found\n");
}

void withdraw()
{
    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);
    int i;
    for (i = 0; i < 1000; i++)
    {
        if (accounts[i]->acno == acno)
        {
            double b;
            printf("Enter the amount you want to withdraw:\n");
            scanf("%lf", &b);
            if (b + 500 > accounts[i]->balance)
            {
                printf("Insufficient balance\n");
                return;
            }
            accounts[i]->balance -= b;
            printf("Available balance: %lf", accounts[i]->balance);
            executeGitCommand("add .");
            executeGitCommand("commit -m \"Amount withdrawn\"");
            return;
        }
    }
    printf("Account not found\n");
}

void closeAccount()
{
    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);
    int i;
    for (i = 0; i < 1000; i++)
    {
        if (accounts[i]->acno == acno)
        {
            while (i + 1 < 1000)
            {
                accounts[i] = accounts[i + 1];
                i++;
            }
            accounts[i] = NULL;
            acindex--;
            executeGitCommand("add .");
            executeGitCommand("commit -m \"Account closed\"");
            return;
        }
    }
    printf("Account not found\n");
}

int main()
{
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        accounts[i] = (Account *)malloc(sizeof(Account));
    }
    i = 0;

    int choice;
    while (1)
    {
        printf("Enter Your Choice:\n");
        printf("\n1.Create a new account\t2.Deposit amount\t3.Withdraw amount\t4.Close Account\t5.Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Account *ac = createAccount();
            accounts[i++] = ac;
            break;

        case 2:
            deposit();
            break;

        case 3:
            withdraw();
            break;

        case 4:
            closeAccount();
            break;

        case 5:
            exit(0);

        default:
            break;
        }
    }
}