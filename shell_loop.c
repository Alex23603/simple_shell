#include "shell.h"

/**
 * strtow2 - Function to split a string into words based on given delimiters.
 * @str: Input string to split.
 * @delims: Delimiters to split the string.
 *
 * Return: An array of strings (words).
 */
char **strtow2(char *str, char *delims)
{
	int i, j, k = 0;
	int word_count = 0;
	char **words;

	if (!str || !delims)
		return (NULL);

	word_count = count_words(str, delims);
	if (word_count == 0)
		return (NULL);

	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0; str[i]; i++)
	{
		if (is_delim(str[i], delims))
			continue;

		for (j = i; str[j] && !is_delim(str[j], delims); j++)
			;

		words[k] = malloc((j - i + 1) * sizeof(char));
		if (!words[k])
		{
			ffree(words);
			return (NULL);
		}

		for (; i < j; i++)
			words[k][i - k] = str[i];
		words[k++][i - k] = '\0';
	}

	words[k] = NULL;
	return (words);
}

/**
 * count_words - Function to count the number of words in a string.
 * @str: Input string.
 * @delims: Delimiters to check for word separation.
 *
 * Return: The number of words in the string.
 */
static int count_words(char *str, char *delims)
{
	int i, count = 0;
	int is_word = 0;

	for (i = 0; str[i]; i++)
	{
		if (!is_delim(str[i], delims))
		{
			if (!is_word)
			{
				count++;
				is_word = 1;
			}
		}
		else
		{
			is_word = 0;
		}
	}

	return (count);
}

/**
 * is_delim - Function to check if a character is a delimiter.
 * @c: The character to check.
 * @delims: The string containing delimiters.
 *
 * Return: 1 if the character is a delimiter, otherwise 0.
 */
static int is_delim(char c, char *delims)
{
	int i;

	for (i = 0; delims[i]; i++)
	{
		if (c == delims[i])
			return (1);
	}

	return (0);
}

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
			info.argv = strtow2(info.arg, " \t\r\n\a");
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
