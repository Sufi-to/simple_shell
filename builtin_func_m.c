#include "shellheader.h"
/**
**builtin_execute - executes the built in functions
**@tokens: arguments being passed
**Return: tokens
**/
int builtin_execute(char **tokens)
{
	struct builtin_executeVariables bev;

	built_s builtin[] = {
		{"exit", exit_shell_wrapper},
		{"env", print_shell_env},
		{NULL, NULL}
	};


	if (tokens[0] == NULL)
		return (1);

	bev.length = _stringlen(tokens[0]);

	bev.num = shell_num_builtins(builtin);
	for (bev.i = 0; bev.i < bev.num; bev.i++)
	{
		if (_strcmp(tokens[0], builtin[bev.i].name, bev.length) == 0)
		{
			bev.status = (builtin[bev.i].p)();
			return (bev.status);
		}
	}
	return (1);
}

/**
**shell_num_builtins - this check num built-ins
**@builtin: takes the builtin to be counted
**Return: num of built-ins
**/

int shell_num_builtins(built_s builtin[])
{
	unsigned int i;

	i = 0;
	while (builtin[i].name != NULL)
		i++;

	return (i);
}
/**
 * print_shell_env - prints environment
 * Return: void
 */
int print_shell_env(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _stringlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 * exit_shell - exits shell
 * @arg: ponter to error message
 * Return: exit
*/
int exit_shell(char *arg)
{
	if (arg != NULL)
	{
		int status;

		status = atoi(arg);
		exit(status);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

/**
 * exit_shell_wrapper - exits shell
 *
 * Return: exit
*/
int exit_shell_wrapper(void)
{
	return (-1);
}


