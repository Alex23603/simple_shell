#include "shell.h"

/**
 * loophsh - Main loop for the shell.
 * @env: Array of environment variables.
 *
 * Return: Always 0.
 */
int loophsh(char **env)
{
	info_t info[] = { INFO_INIT };
	ssize_t read_status;

	info->environ = env;

	signal(SIGINT, sigintHandler);
	if (!isatty(STDIN_FILENO))
		info->linecount_flag = 0;
	do {
		if (isatty(STDIN_FILENO))
			_puts("$ ");
		clear_info(info);
		read_status = get_input(info);
		if (read_status == EOF)
			break;
		if (_strcmp(info->arg, "\n") == 0)
			continue;
		info->argv = strtow2(info->arg, " \t\r\n\a");
		if (!info->argv)
		{
			free_info(info, 0);
			break;
		}
		if (find_builtin(info) == 0)
			find_cmd(info);
		free_info(info, 1);
	} while (1);
	return (info->status);
}
