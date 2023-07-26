#include "shell.h"

/**
 * _erratoi - converts string to integer
 * @str: the string to convert
 *
 * Return: the integer value, or -1 on error
 */
int _erratoi(char *str)
{
	int num = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + (str[i] - '0');
		i++;
	}

	return (num * sign);
}

/**
 * print_error - prints error messages to stderr
 * @av: the program name
 * @cmd: the command that caused the error
 * @count: the command count
 */
void print_error(char *av, char *cmd, int count)
{
	_puts(av);
	_puts(": ");
	print_number(count);
	_puts(": ");
	_puts(cmd);
	_puts(": not found\n");
}
