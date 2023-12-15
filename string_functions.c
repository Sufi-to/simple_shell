#include "shellheader.h"

/**
 * _strcmp - finds if two strings are the exactly equal
 * @name: string to search for
 * @var: variable to compare against
 * @len: length of name
 * Return: 1 if strings are equal else -1
 */
int _strcmp(char *name, char *var, unsigned int len)
{
	unsigned int var_length;
	unsigned int i;

	var_length = _stringlen(var);
	if (var_length != len)
		return (-1);

	i = 0;
	while (name[i] != '\0' && var[i] != '\0')
	{
		if (name[i] != var[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * _stringncmp - compares two strings
 * up to given length are the same
 * @name: name to be compared
 * @str: string to compare against
 * @len: length for comparing
 * Return: 1 if strings are equal, -1 if they are not
 */
int _stringncmp(char *name, char *str, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		if (name[i] != str[i])
			return (-1);
		i++;
	}
	return (1);
}

/**
 * *_stringcpy - copies string pointed to by src to the buffer pointed to dest
 * @dest: destination for the copied string
 * @src: source of the string to be copied
 * Return: the pointer to dest
 */
char *_stringcpy(char *dest, char *src)
{
	int i, len;

	len = 0;
	i = 0;
	while (src[len] != '\0')
	{
		len++;
	}
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';

	return (dest);
}

/**
 * _stringlen - returns the length of a string
 * @s: string whose length will be found
 * Return: string length
 */
int _stringlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return (i);
}

