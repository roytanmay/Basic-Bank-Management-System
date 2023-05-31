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

void executeGitCommand(const char *command)
{
    // printf("hi");
    char gitCommand[100];
    snprintf(gitCommand, sizeof(gitCommand), "git %s", command);
    int result = system(gitCommand);
    if (result == -1)
    {
        printf("Failed to execute Git command.\n");
    }
}

void createAccount()
{
    FILE *ptr;
    ptr = fopen("record.dat", "a+");

    Account *account = (Account *)malloc(sizeof(Account));
    printf("Enter your name:\n");
    scanf("%s", &account->name);
    printf("Enter your address:\n");
    scanf("%s", &account->address);
    printf("Enter the amount you want to deposit initially(>= 500):\n");
    scanf("%lf", &account->balance);
    account->acno = acnoInit++;

    fprintf(ptr, "%d %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    fclose(ptr);

    printf("Account Created Successfully\n");

    // accounts[acindex++] = account;

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
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%d %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            double b;
            printf("Enter the amount you want to deposit:\n");
            scanf("%lf", &b);
            account->balance += b;
            printf("Amount deposited\nAvailable balance: %lf\n\n", account->balance);
            // executeGitCommand("status");
            executeGitCommand("add .");
            executeGitCommand("commit -m \"Balance deposited\"");

            f = 1;
        }
        fprintf(newrec, "%d %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (f == 0)
        printf("Account not found\n");
}

void withdraw()
{
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%d %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            double b;
            printf("Enter the amount you want to withdraw:\n");
            scanf("%lf", &b);
            account->balance -= b;
            printf("Amount Withdrawn\nAvailable balance: %lf\n\n", account->balance);
            // executeGitCommand("status");
            executeGitCommand("add .");
            executeGitCommand("commit -m \"Balance Withdrawn\"");

            f = 1;
        }
        fprintf(newrec, "%d %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (f == 0)
        printf("Account not found\n");
}

void closeAccount()
{
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    int acno;
    printf("Enter your account number:\n");
    scanf("%d", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%d %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            f = 1;
            printf("Account deleted\n");
        }
        else
            fprintf(newrec, "%d %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (f == 0)
        printf("Account not found\n");
    else
    {
        executeGitCommand("add .");
        executeGitCommand("commit -m \"Account Deleted\"");
    }
}

int main()
{
    int choice;
    while (1)
    {
        printf("Enter Your Choice:\n");
        printf("\n1.Create a new account\t2.Deposit amount\t3.Withdraw amount\t4.Close Account\t5.Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
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