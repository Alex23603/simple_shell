#include "shell.h"

/**
 * getLine - Read a line of input from the user
 * Return: The line of input, or NULL on failure or end of file
 */
char *getLine(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t n_read;

	n_read = getline(&line, &bufsize, stdin);
	if (n_read == -1)
	{
		if (feof(stdin)) /* End of file (Ctrl+D) */
		{
			free(line);
			_eputchar('\n');
			exit(EXIT_SUCCESS);
		}
		perror("getline");
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * remove_comments - Remove comments from an input buffer
 * @buffer: The input buffer
 */
void remove_comments(char *buffer)
{
	int i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '#')
		{
			while (buffer[i] && buffer[i] != '\n')
				buffer[i++] = ' ';
			break;
		}
		i++;
	}
}
