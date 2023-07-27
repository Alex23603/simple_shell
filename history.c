#include "shell.h"

/**
 * _putsfd - Prints a string to a specific file descriptor.
 * @str: The input string to print.
 * @fd: The file descriptor to write to.
 */
void _putsfd(char *str, int fd)
{
	ssize_t len = _strlen(str);

	write(fd, str, len);
}

/**
 * print_error - Prints errors related to built-in commands.
 * @argv0: The name of the program.
 * @cmd: The command that caused the error.
 * @count: The command counter.
 */
void print_error(char *argv0, char *cmd, int count)
{
	char error_msg[1024];

	sprintf(error_msg, "%s: %d: %s: not found\n", argv0, count, cmd);
	_putsfd(error_msg, STDERR_FILENO);
}

/**
 * print_number - Prints a number to the standard output stream.
 * @n: The number to print.
 */
void print_number(int n)
{
	char buffer[20];
	int i, j, digit, neg;

	if (n == 0)
	{
		_putchar('0');
		return;
	}

	if (n < 0)
	{
		neg = 1;
		n = -n;
	}

	while (n != 0)
	{
		digit = n % 10;
		buffer[i++] = digit + '0';
		n /= 10;
	}

	if (neg)
		buffer[i++] = '-';

	for (j = i - 1; j >= 0; j--)
		_putchar(buffer[j]);
}

/**
 * add_history - Adds a command to the shell history.
 * @history: The history struct.
 * @command: The command to add.
 */
void add_history(history_t *history, char *command)
{
	history_t *new_node, *temp;

	if (!command || !history)
		return;

	new_node = malloc(sizeof(history_t));
	if (!new_node)
		return;

	new_node->command = _strdup(command);
	new_node->next = NULL;

	if (!history->history)
	{
		history->history = new_node;
		history->count = 1;
	}
	else
	{
		temp = history->history;
		while (temp->next)
			temp = temp->next;

		temp->next = new_node;
		history->count++;
	}
}

/**
 * free_history - Frees the memory allocated for the shell history.
 * @history: The history struct.
 */
void free_history(history_t *history)
{
	history_t *temp;

	if (!history)
		return;

	while (history->history)
	{
		temp = history->history;
		history->history = history->history->next;
		free(temp->command);
		free(temp);
	}

	free(history);
}
