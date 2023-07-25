#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

/**
 * tokenize_arguments - Tokenize the given command string into arguments.
 * @command: The command string to tokenize.
 * @arguments: An array of strings to store the arguments.
 *
 * This function takes a command string and tokenizes it into individual
 * arguments, separated by spaces. The tokenized arguments are stored in the
 * 'arguments' array, and the number of arguments tokenized is returned.
 *
 * Return: The number of arguments tokenized. If the command is empty or no
 * arguments are found, it returns 0.
 */
int tokenize_arguments(char *command, char **arguments);

/**
 * find_executable - Search for the executable command in the PATH.
 * @command: The command to find in the PATH.
 *
 * This function searches for the executable command in the directories
 * specified by the PATH environment variable. If found, it returns the
 * full path to the command; otherwise, it returns NULL.
 *
 * Return: The full path to the command if found, otherwise NULL.
 */
char *find_executable(char *command);

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
printf("($) ");
if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
printf("\n");
break;
}

/*Remove the newline character at the end of the command*/
command[strcspn(command, "\n")] = '\0';

num_arguments = tokenize_arguments(command, arguments);
if (num_arguments > 0)
{
if (strcmp(arguments[0], "exit") == 0)
{
exit(EXIT_SUCCESS);
}
execute_command(arguments, num_arguments);
}
}

return (0);
}

/**
 * tokenize_arguments - Tokenize the given command string into arguments.
 * @command: The command string to tokenize.
 * @arguments: An array of strings to store the arguments.
 *
 * This function takes a command string and tokenizes it into individual
 * arguments, separated by spaces. The tokenized arguments are stored in the
 * 'arguments' array, and the number of arguments tokenized is returned.
 *
 * Return: The number of arguments tokenized. If the command is empty or no
 * arguments are found, it returns 0.
 */
int tokenize_arguments(char *command, char **arguments)
{
int num_arguments = 0;
char *token = NULL;
char *rest = command;

while ((token = strtok_r(rest, " ", &rest)) != NULL &&
	num_arguments < MAX_NUM_ARGUMENTS)

{
arguments[num_arguments++] = token;
}

return (num_arguments);
}

/**
 * find_executable - Search for the executable command in the PATH.
 * @command: The command to find in the PATH.
 *
 * This function searches for the executable command in the directories
 * specified by the PATH environment variable. If found, it returns the
 * full path to the command; otherwise, it returns NULL.
 *
 * Return: The full path to the command if found, otherwise NULL.
 */
char *find_executable(char *command)
{
char *path = getenv("PATH");
char *dir = strtok(path, ":");

while (dir != NULL)
{
char *executable = malloc(strlen(dir) + strlen(command) + 2);
if (executable == NULL)
{
perror("malloc() failed");
return (NULL);
}

sprintf(executable, "%s/%s", dir, command);

if (access(executable, X_OK) == 0)
{
return (executable);
}

free(executable);
dir = strtok(NULL, ":");
}

return (NULL);
}

/**
 * execute_command - Execute the command with the given arguments.
 * @arguments: An array of strings containing the command and its arguments.
 * @num_arguments: The number of arguments in the arguments array.
 */

void execute_command(char **arguments, int num_arguments)
{
char *executable = find_executable(arguments[0]);

if (executable == NULL)
{
printf("%s: command not found\n", arguments[0]);
return;
}

pid_t pid = fork();

if (pid < 0)
{
perror("fork() failed");
free(executable);
return;
}
else if (pid == 0)
{
/* Child process. */
	execv(executable, arguments);
	perror("Command execution failed");
	_exit(EXIT_FAILURE);
}
else
{
/* Parent process. */
int status;
waitpid(pid, &status, 0);
}

free(executable);
}
