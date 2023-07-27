#include "shell.h"

/**
 * _eputs - Prints a string to the standard error stream.
 * @str: The string to print.
 */
void _eputs(const char *str)
{
	write(STDERR_FILENO, str, _strlen(str));
}

/**
 * _eputchar - Prints a character to the standard error stream.
 * @c: The character to print.
 */
void _eputchar(char c)
{
	write(STDERR_FILENO, &c, 1);
}

/**
 * hsh - Shell's main function.
 */
void hsh(void)
{
	char *line;
	int status;

	do {
		_eputs("#cisfun$ ");
		line = _getline();
		status = process_line(line);
		free(line);
	} while (status);

	_eputchar('\n');
}

/**
 * process_line - Processes a line of input from the user.
 * @line: The input line.
 *
 * Return: 0 if the shell should continue, 1 if the shell should exit.
 */
int process_line(char *line)
{
	/* Add the implementation of processing the command here */

	/* For now, let's exit the shell if the user enters "exit" */
	if (_strncmp(line, "exit", 4) == 0)
		return (0);

	return (1);
}
/**
 * main - Entry point for the simple shell program.
 *
 * Description: This function initializes the shell and enters the main loop
 *              to read commands from the user and execute them.
 *
 * Return: Always 0.
 */
int main(void)
{
	hsh();
	return (0);
}
