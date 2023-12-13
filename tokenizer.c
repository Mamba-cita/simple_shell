#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat confines are ignored
 * @str: the input string
 * @d: the confine string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, tot_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_conf(str[i], d) && (is_conf(str[i + 1], d) || !str[i + 1]))
			tot_words++;

	if (tot_words == 0)
		return (NULL);
	s = malloc((1 + tot_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < tot_words; j++)
	{
		while (is_conf(str[i], d))
			i++;
		k = 0;
		while (!is_conf(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the confine
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, tot_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			tot_words++;
	if (tot_words == 0)
		return (NULL);
	s = malloc((1 + tot_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < tot_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
