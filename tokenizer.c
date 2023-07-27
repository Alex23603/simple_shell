#include "shell.h"

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The string containing delimiters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}
