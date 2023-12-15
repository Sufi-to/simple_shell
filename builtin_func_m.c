#include "shellheader.h"
/**
**builtin_execute - executes the built in functions
**@tokens: arguments being passed
**Return: token num
**/
int builtin_execute(char **tokens)
{
	struct builtin_executeVariables be_var;

	built_s builtin[] = {
		{"exit", exit_shell_wrapper},
		{"env", print_shell_env},
		{NULL, NULL}
	};


	if (tokens[0] == NULL)
		return (1);

	be_var.length = _stringlen(tokens[0]);

	be_var.num = shell_num_builtins(builtin);
	for (be_var.i = 0; be_var.i < be_var.num; be_var.i++)
	{
		if (_strcmp(tokens[0], builtin[be_var.i].name, be_var.length) == 0)
		{
			be_var.status = (builtin[be_var.i].p)();
			return (be_var.status);
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
	unsigned int num;

	num = 0;
	while (builtin[num].name != NULL)
		num++;

	return (num);
}
/**
 * print_shell_env - prints environment
 * Return: void
 */
int print_shell_env(void)
{
	unsigned int num;

	num = 0;
	while (environ[num] != NULL)
	{
		write(STDOUT_FILENO, environ[num], _stringlen(environ[num]));
		write(STDOUT_FILENO, "\n", 1);
		num++;
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


