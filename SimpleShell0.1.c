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

	/*Rest of the code remains unchanged*/

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
char *token = strtok(command, " ");

while (token != NULL && num_arguments < MAX_NUM_ARGUMENTS)
{
arguments[num_arguments++] = token;
token = strtok(NULL, " ");
}

return (num_arguments);
}

/**
 * execute_command - Execute the command with the given arguments.
 * @arguments: An array of strings containing the command and its arguments.
 * @num_arguments: The number of arguments in the arguments array.
 */

void execute_command(char **arguments, int num_arguments)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork() failed");
		return;
	}
	else if (pid == 0)
	{
		/* Child process. */
		execvp(arguments[0], arguments);
		perror("Command not found");
		_exit(1);
	}
	else
	{
		/* Parent process. */
		int status;

		waitpid(pid, &status, 0);

	}

}
