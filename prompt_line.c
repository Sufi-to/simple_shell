#include "shellheader.h"

/**
 * prompt_sh - checks mode and prints prompt if in interactive mode
 * @fd: file stream
 * @buff: buffer
**/
void prompt_sh(int fd, struct stat buff)
{
	fstat(fd, &buff);

	if (S_ISCHR(buff.st_mode))
		_puts("): ");
}

/**
 * _puts - prints a string without a \n
 * @s: string to print
 * Return: void
 */
void _puts(char *s)
{
	unsigned int len;

	len = _stringlen(s);
	write(STDOUT_FILENO, s, len);
}

