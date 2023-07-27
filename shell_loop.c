#include "shell.h"

/**
 * find_cmd - Find the appropriate command in the PATH
 * @cmd: The command to find
 * @path: The PATH environment variable
 * Return: The full path of the command, or NULL if not found
 */
char *find_cmd(char *cmd, char *path)
{
	char **dirs, *full_path;
	int i;
	struct stat st;

	if (!path || !cmd)
		return (NULL);

	dirs = strtow(path, ":");
	if (!dirs)
		return (NULL);

	full_path = malloc(PATH_MAX);
	if (!full_path)
	{
		free_tokens(dirs);
		return (NULL);
	}

	for (i = 0; dirs[i]; i++)
	{
		_memset(full_path, 0, PATH_MAX);
		_strcat(full_path, dirs[i]);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);

		if (stat(full_path, &st) == 0)
		{
			free_tokens(dirs);
			return (full_path);
		}
	}

	free_tokens(dirs);
	free(full_path);
	return (NULL);
}

/**
 * shell_loop - The shell's main loop
 * @env: The environment variables
 * Return: None
 */
void shell_loop(char **env)
{
	char *line, **tokens, *cmd;
	int status;

	do {
		_prompt();
		line = _getline();
		if (!line)
			break;

		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue;
		}

		cmd = find_cmd(tokens[0], _getenv("PATH", env));
		if (cmd)
		{
			status = execute_cmd(cmd, tokens, env);
			free(cmd);
		}
		else
		{
			print_error(tokens[0], "not found");
			status = 127;
		}

		free_tokens(tokens);
		free(line);
	} while (status);

	exit(status);
}
