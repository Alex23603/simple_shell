#include "shell.h"

/**
 * strtow2 - Splits a string into an array of words (with custom delimiters)
 * @str: The input string to be split
 * @delims: The delimiters used for splitting
 *
 * Return: Pointer to an array of strings (words)
 */
char **strtow2(char *str, char *delims)
{
	int i, j, k, word_count = 0, len;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	len = _strlen(str);
	words = malloc((len + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);

	for (i = 0, k = 0; str[i]; i++)
	{
		if (!_strchr(delims, str[i]))
		{
			for (j = i; str[j] && !_strchr(delims, str[j]); j++)
				;
			words[k] = malloc((j - i + 1) * sizeof(char));
			if (words[k] == NULL)
			{
				for (k--; k >= 0; k--)
					free(words[k]);
				free(words);
				return (NULL);
			}

			for (; i < j; i++)
				words[k][i - k] = str[i];
			words[k++][i - k] = '\0';
			word_count++;
		}
	}

	words[word_count] = NULL;
	return (words);
}

int loophsh(char **env)
{
	info_t info = INFO_INIT;

	/* Initialize the history list */
	info.history = add_node_end(&info.history, NULL, 0);

	/* Set the initial values */
	info.argv = NULL;
	info.environ = env;
	info.status = 0;

	/* Ignore SIGINT (Ctrl+C) to prevent termination */
	signal(SIGINT, sigintHandler);

	/* Read commands from stdin and execute them */
	while (get_input(&info) != -1)
	{
		if (info.arg && *info.arg)
		{
			info.arg = replace_alias(&info);
			if (!info.arg || !_strcmp(info.arg, ""))
			{
				free(info.arg);
				continue;
			}

			/* Tokenize the input command */
			info.argv = strtow2(info.arg, " \t\r\n\a");
			if (!info.argv)
			{
				free(info.arg);
				continue;
			}

			/* Find and execute the command */
			find_cmd(&info);
			free_info(&info, 0);
		}
	}
	write_history(&info);
	free_list(&info.history);
	return (info.status);
}
