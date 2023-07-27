#include "shell.h"

/**
 * convert_number - Convert a number to a string
 * @num: The number to convert
 * Return: A string representing the number, NULL on failure
 */
char *convert_number(int num)
{
	int num_digits = 0, copy, i;
	char *str_num;

	if (num == 0)
		num_digits = 1;
	else
	{
		copy = num;
		while (copy != 0)
		{
			num_digits++;
			copy /= 10;
		}
	}

	str_num = malloc((num_digits + 1) * sizeof(char));
	if (!str_num)
		return (NULL);

	if (num == 0)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
	}
	else
	{
		for (i = num_digits - 1; i >= 0; i--)
		{
			str_num[i] = (num % 10) + '0';
			num /= 10;
		}
		str_num[num_digits] = '\0';
	}

	return (str_num);
}
