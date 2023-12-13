#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_conf - checks if character is a confine
 * @c: the char to check
 * @conf: the confine string
 * Return: 1 if true, 0 if false
 */
int is_conf(char c, char *conf)
{
	while (*conf)
		if (*conf++ == c)
			return (1);
	return (0);
}

/**
 * _ischar - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _ischar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, boolean = 0, output;
	null int result = 0;

	for (i = 0; s[i] != '\0' && boolean != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			boolean = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (boolean == 1)
			boolean = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}