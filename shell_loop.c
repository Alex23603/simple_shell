/* shell_loop.c */

#include "shell.h"

/**
 * find_cmd - finds the full path of the command to execute
 * @info: the info struct
 */
void find_cmd(info_t *info)
{
	char *cmd = "not found"; /* Assign the appropriate value to cmd */

	/* Your implementation of find_cmd here */

	print_error(info, cmd, 127);
}

/**
 * fork_cmd - forks the shell to execute a command
 * @info: the info struct
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	/* Your implementation of fork_cmd here */

	if (child_pid == -1)
	{
		char *cmd = "Permission denied"; /* Assign the appropriate value to cmd */
		print_error(info, cmd, 126);
	}
}

/**
 * loophsh - main loop for the simple shell
 * @env: the current environment
 *
 * Return: Always 0 on success
 */
int loophsh(char **env)
{
	info_t info[] = { INFO_INIT };
	size_t size;
	char *line = NULL;
	int status = 0;

	/* Set up initial info */
	set_info(info, env);

	/* Loop for shell */
	while (status != -1)
	{
		if (isatty(STDIN_FILENO))
			_putsfd("#cisfun$ ", STDERR_FILENO);

		/* Read input line */
		if (!get_input(info))
		{
			free_info(info, 0);
			break;
		}

		/* Tokenize input line */
		info->argv = strtow2(info->arg, " \t\r\n\a");

		if (!info->argv || !info->argv[0])
		{
			bfree((void **)&info->arg);
			free_info(info, 1);
			continue;
		}

		/* ... existing code ... */

		/* Free allocated memory */
		bfree((void **)&info->arg);
		bfree((void **)&info->argv);
	}
	return (status);
}

