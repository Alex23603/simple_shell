#include "shell.h"

/**
 * print_error - Prints an error message to the standard error stream.
 * @msg: The error message to print.
 * @argv0: The name of the program (argv[0]) to include in the error message.
 */
void print_error(const char *msg, const char *argv0)
{
	_puts(argv0);
	_puts(": ");
	_puts(msg);
	_puts("\n");
}

/**
 * print_number - Prints a number to the standard output stream.
 * @n: The number to print.
 */
void print_number(int n)
{
	char buffer[20];
	int i = 0, is_negative = 0;

	if (n == 0)
	{
		_putchar('0');
		return;
	}

	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}

	while (n != 0)
	{
		buffer[i++] = n % 10 + '0';
		n /= 10;
	}

	if (is_negative)
		_putchar('-');

	while (--i >= 0)
		_putchar(buffer[i]);
}

/**
 * _myexit - The implementation of the exit built-in command.
 * @args: The arguments passed to the exit command (should be empty).
 * @env: The current environment variables.
 * Return: 0 on success, -1 on failure.
 */
int _myexit(char **args, char **env)
{
	(void)env;

	if (!args[1])
		exit(EXIT_SUCCESS);

	if (_atoi(args[1]) == -1)
	{
		print_error("Illegal number: ", args[0]);
		return (-1);
	}

	exit(_atoi(args[1]));
}

/**
 * _mycd - The implementation of the cd built-in command.
 * @args: The arguments passed to the cd command.
 * @env: The current environment variables.
 * Return: 0 on success, -1 on failure.
 */
int _mycd(char **args, char **env)
{
	char *new_dir;

	if (args[1] == NULL)
		new_dir = _getenv("HOME", env);
	else if (_strcmp(args[1], "-") == 0)
	{
		new_dir = _getenv("OLDPWD", env);
		_puts(new_dir);
		_puts("\n");
	}
	else
		new_dir = args[1];

	if (!new_dir)
	{
		print_error("No HOME variable in the environment", args[0]);
		return (-1);
	}

	if (chdir(new_dir) != 0)
	{
		print_error("can't cd to ", args[0]);
		return (-1);
	}

	_setenv("OLDPWD", _getenv("PWD", env), &env);
	_setenv("PWD", new_dir, &env);

	return (0);
}
