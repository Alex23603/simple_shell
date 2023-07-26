#include "shell.h"

/**
 * loophsh - The main loop of the shell.
 * @environ: The array of environment variables.
 *
 * Return: 0 on success, otherwise 1.
 */
int loophsh(char **environ)
{
	info_t info;
	int exit_status = 0;

	set_info(&info, environ);

	do {
		if (info.linecount_flag)
			info.line_count++;

		if (get_input(&info) == EOF)
			break;

		if (info.arg[0] != '\n' && info.arg[0] != 0)
		{
			info.argv = strtow(info.arg, " \t\r\n\a");
			if (info.argv == NULL)
				continue;
			find_cmd(&info);
		}
		free_info(&info, 1);
	} while (exit_status == 0);

	free_info(&info, 1);
	free_list(&(info.env));

	return (exit_status);
}
