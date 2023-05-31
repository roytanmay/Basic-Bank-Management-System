#include <stdio.h>
#include <stdlib.h>

typedef struct Account
{
    char name[100];
    long long acno;
    char address[100];
    double balance;
} Account;

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

void createAccount()
{
    printf("\n\n");

    FILE *ptr, *ptr2, *ptr3;
    ptr = fopen("record.dat", "a+");
    ptr2 = fopen("accountNumber.dat", "r");

    Account *account = (Account *)malloc(sizeof(Account));
    printf("Enter your name:\n");
    scanf("%s", account->name);
    printf("Enter your address:\n");
    scanf("%s", account->address);
    printf("Enter the amount you want to deposit initially(>= 500):\n");
    scanf("%lf", &account->balance);

    fscanf(ptr2, "%lld", &account->acno);
    fclose(ptr2);

    ptr3 = fopen("accountNumber.dat", "w");
    fprintf(ptr3, "%lld", account->acno + 1);
    fclose(ptr3);

    fprintf(ptr, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    fclose(ptr);

    printf("\nAccount Created Successfully\n");

    // accounts[acindex++] = account;

    printf("\nAccount Details:\n");
    printf("Name: %s\n", account->name);
    printf("Address: %s\n", account->address);
    printf("Account number: %lld\n", account->acno);
    printf("Balance: %lf\n", account->balance);
    printf("\n\n");

    executeGitCommand("add .");
    executeGitCommand("commit -m \"New Account Created\"");
    printf("\n\n");
}

void deposit()
{
    printf("\n\n");
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    long long acno;
    printf("Enter your account number:\n");
    scanf("%lld", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%lld %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            double b;
            printf("Enter the amount you want to deposit:\n");
            scanf("%lf", &b);
            account->balance += b;
            printf("Amount deposited\nAvailable balance: %lf\n\n", account->balance);
            // fprintf(newrec, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);

            f = 1;
        }
        fprintf(newrec, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);

    printf("\n\n");

    if (f == 0)
    {
        printf("Account not found\n");
        remove("new.dat");
    }
    else
    {
        // executeGitCommand("status");
        remove("record.dat");
        rename("new.dat", "record.dat");
        executeGitCommand("add .");
        executeGitCommand("commit -m \"Balance deposited\"");
    }

    printf("\n\n");
}

void withdraw()
{
    printf("\n\n");

    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    long long acno;
    printf("Enter your account number:\n");
    scanf("%lld", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%lld %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            double b;
            printf("Enter the amount you want to withdraw:\n");
            scanf("%lf", &b);
            account->balance -= b;
            printf("Amount Withdrawn\nAvailable balance: %lf\n\n", account->balance);

            // fprintf(newrec, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);

            f = 1;
        }
        fprintf(newrec, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);

    printf("\n\n");

    if (f == 0)
    {
        printf("Account not found\n");
        remove("new.dat");
    }
    else
    {
        // executeGitCommand("status");
        remove("record.dat");
        rename("new.dat", "record.dat");
        executeGitCommand("add .");
        executeGitCommand("commit -m \"Balance Withdrawn\"");
    }

    printf("\n\n");
}

void closeAccount()
{
    printf("\n\n");

    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    long long acno;
    printf("Enter your account number:\n");
    scanf("%lld", &acno);

    Account *account = (Account *)malloc(sizeof(Account));

    int f = 0;

    while (fscanf(old, "%lld %s %s %lf", &account->acno, &account->name, &account->address, &account->balance) != EOF)
    {
        if (account->acno == acno)
        {
            f = 1;
            printf("Account deleted\n");
        }
        else
            fprintf(newrec, "%lld %s %s %lf\n", account->acno, account->name, account->address, account->balance);
    }
    fclose(newrec);
    fclose(old);

    printf("\n\n");

    if (f == 0)
    {
        printf("Account not found\n");
        remove("new.dat");
    }
    else
    {
        remove("record.dat");
        rename("new.dat", "record.dat");
        executeGitCommand("add .");
        executeGitCommand("commit -m \"Account Deleted\"");
    }

    printf("\n\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n1.Create a new account\t2.Deposit amount\t3.Withdraw amount\t4.Close Account\t5.Exit\n");
        printf("\nEnter Your Choice:\n");
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