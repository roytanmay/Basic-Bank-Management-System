#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    // Example usage:
    executeGitCommand("status");
    // executeGitCommand("add .");
    // executeGitCommand("commit -m \"Initial commit\"");
    // executeGitCommand("push origin master");

    return 0;
}
