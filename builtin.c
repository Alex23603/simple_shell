#include "shell.h"

/**
 * print_error - prints error messages
 * @info: the info struct
 * @cmd: the command that caused the error
 * @count: the error count
 */
void print_error(info_t *info, char *cmd, int count)
{
	_putsfd(info->fname, 2);
	_putsfd(": ", 2);
	print_number(count); /* Fixed: Add the correct function call */
	_putsfd(": ", 2);
	_putsfd(cmd, 2);
	_putsfd(": not found\n", 2);
}

/**
 * print_number - prints a number
 * @count: the number to print
 */
static void print_number(int count)
{
	char c = count % 10 + '0';
	int length = 0, num = count;

	while (num != 0)
	{
		num /= 10;
		length++;
	}
	if (count > 9)
		_putfd((count / 10) + '0', 2);
	_putfd(c, 2);
}

/**
 * _myexit - exit built-in command
 * @info: the info struct
 * Return: always returns 1, to continue execution
 */
int _myexit(info_t *info)
{
	int status = 0;

	if (info->argv[1])
	{
		status = _erratoi(info->argv[1]);
		if (status < 0)
		{
			info->err_num = 2;
			print_error(info, info->argv[0], info->line_count);
			return (1);
		}
	}

	free_info(info, 1);
	free_list(&(info->env));
	free_list(&(info->history));
	free_list(&(info->alias));
	free_list(&(info->env));
	if (info->cmd_buf)
	{
		while (*(info->cmd_buf))
			free(*((info->cmd_buf)++));
		free(info->cmd_buf);
	}
	exit(status);
	return (1);
}

/**
 * _mycd - change directory built-in command
 * @info: the info struct
 * Return: always returns 1, to continue execution
 */
int _mycd(info_t *info)
{
	char *home = _getenv(info, "HOME");
	char *oldpwd = _getenv(info, "OLDPWD");
	char *pwd = _getenv(info, "PWD");
	char *dest;

	if (info->argc > 2)
	{
		info->err_num = 2;
		print_error(info, info->argv[0], info->line_count);
		return (1);
	}

	if (info->argv[1] == NULL || _strcmp(info->argv[1], "~") == 0)
		dest = home;
	else if (_strcmp(info->argv[1], "-") == 0)
		dest = oldpwd;
	else
		dest = info->argv[1];

	if (chdir(dest) == -1)
	{
		info->err_num = 2;
		print_error(info, info->argv[0], info->line_count);
		return (1);
	}

	if (dest == home)
		dest = _getenv(info, "PWD");
	if (dest == oldpwd)
	{
		dest = pwd;
		printf("%s\n", dest);
	}
	_setenv(info, "OLDPWD", pwd);
	_setenv(info, "PWD", dest);

	return (1);
}

/**
 * _myhelp - help built-in command
 * @info: the info struct
 * Return: always returns 1, to continue execution
 */
int _myhelp(info_t *info)
{
	(void)info;
	_puts("Type programs to run them.\n");
	_puts("Commands:\n");
	_puts("  help\n");
	_puts("  exit\n");
	_puts("  cd [DIR]\n");
	_puts("  env\n");
	_puts("  setenv [VAR] [VALUE]\n");
	_puts("  unsetenv [VAR]\n");
	_puts("  history\n");
	_puts("  alias [NAME[='VALUE'] ...]\n");
	_puts("  history\n");
	return (1);
}
