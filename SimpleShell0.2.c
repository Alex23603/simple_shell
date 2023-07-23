#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

/**
 * tokenize_command - Tokenize the given command string into arguments.
 * @command: The command string to tokenize.
 * @arguments: An array of strings to store the arguments.
 *
 * Return: The number of arguments tokenized.
 */
int tokenize_command(char *command, char **arguments);

/**
 * execute_command - Execute the command with the given arguments.
 * @arguments: An array of strings containing the command and its arguments.
 * @num_arguments: The number of arguments in the arguments array.
 */
void execute_command(char **arguments, int num_arguments);

/**
 * main - Entry point of the Simple Shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_NUM_ARGUMENTS];
    int num_arguments;

    while (1)
    {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
            break;

        // Remove trailing newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command
        num_arguments = tokenize_command(command, arguments);

        // Execute the command
        execute_command(arguments, num_arguments);
    }

    return 0;
}

int tokenize_command(char *command, char **arguments)
{
    int num_arguments = 0;
    char *token = strtok(command, " ");
    while (token != NULL)
    {
        arguments[num_arguments] = token;
        num_arguments++;
        token = strtok(NULL, " ");
    }
    return num_arguments;
}

void execute_command(char **arguments, int num_arguments)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        execvp(arguments[0], arguments);
        perror(arguments[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}
