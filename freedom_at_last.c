#include "shellheader.h"

/**
 * free_all - frees all malloc'd space at end of main loop
 * @tokens: pointer to tokens array
 * @path: pointer to path variable
 * @line: pointer to user input buffer
 * @fullpath: pointer to full path
 * @flag: flag marking if full_path was malloc'd
 * Return: void
 */
void free_all(char **tokens, char *path, char *line, char *fullpath, int flag)
{
	free(path);
	free(tokens);
	free(line);
	if (flag == 1)
		free(fullpath);
}

/**
 * free_double - free double pointer
 * @arr: double pointer to free
 * @len: length of double pointer
 * Return: void
 */
void free_double(char **arr, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * _getlinefromstd - gets the input from the stdin
 * @inp: buffer for user input
 * Return: buffer with user input
 */
char *_getlinefromstd(FILE *inp)
{
	char *line_to_read;
	ssize_t read;
	size_t len;

	line_to_read = NULL;
	len = 0;
	read = getline(&line_to_read, &len, inp);
	if (read == -1)
	{
		free(line_to_read);
		exit(EXIT_SUCCESS);
	}

	return (line_to_read);
}

