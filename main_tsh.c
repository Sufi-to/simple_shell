#include "shellheader.h"

/**
 * initialize_variables - Initializes variables used in the
 * main execution loop.
 * @mFV: Pointer to the mainFunctionVariables structure.
 * @buff: Pointer to the stat structure.
 *
 * Description: This function sets initial values for various variables used
 *              in the main execution loop of the shell.
 *
 * Return: None.
 */
void initialize_variables(struct mainFunctionVariables *mFV, struct stat *buff)
{
	memset(buff, 0, sizeof(struct stat));

	mFV->line = NULL;
	mFV->tokens = NULL;
	mFV->builtin_status = 0;
	mFV->flag = 0;
	mFV->path = NULL;
	mFV->fullpath = NULL;
	mFV->child_status = 0;
}

/**
 * main_execution_loop - Executes the main loop of the shell.
 * @mFV: Pointer to the struct containing main function variables.
 * @buff: Pointer to the struct stat for file status information.
 *
 * Description:
 *   This function runs the main loop of the shell, continuously prompting
 *   the user for input, parsing the input into tokens, and executing
 *   the corresponding commands. It handles built-in commands, such as "cd",
 *   and external commands using custom functions like cd_shell,
 *  builtin_execute,
 *   findExecutablePath, and execute_command.
 *   The loop continues until an exit condition is met, such as
 * the user entering
 *   a specific command or an error occurring during command execution.
 *
 * Return: This function does not return as it continuously executes
 * the shell loop.
 */
void main_execution_loop(struct mainFunctionVariables *mFV, struct stat *buff)
{
	while (1)
	{
		prompt_sh(STDIN_FILENO, *buff);
		mFV->line = _getlinefromstd(stdin);
		if (_strcmp(mFV->line, "\n", 1) == 0)
		{
			free(mFV->line);
			continue;
		}
		mFV->tokens = customTokenizer(mFV->line);
		if (mFV->tokens[0] == NULL)
			continue;
		if (_strcmp(mFV->tokens[0], "cd", _stringlen("cd")) == 0)
			cd_shell(mFV);
		else
			mFV->builtin_status = builtin_execute(mFV->tokens);
		if (mFV->builtin_status == 0 || mFV->builtin_status == -1)
		{
			free(mFV->tokens);
			free(mFV->line);
		}
		if (mFV->builtin_status == 0)
			continue;
		if (mFV->builtin_status == -1)
			_exit(EXIT_SUCCESS);
		mFV->flag = 0;
		mFV->path = _getenv("PATH");
		mFV->fullpath = findExecutablePath(mFV->tokens[0], mFV->fullpath, mFV->path);
		if (mFV->fullpath == NULL)
			mFV->fullpath = mFV->tokens[0];
		else
			mFV->flag = 1;
		mFV->child_status = execute_command(mFV->fullpath, mFV->tokens);
		if (mFV->child_status == -1)
			handle_errors(2);
		free_all(mFV->tokens, mFV->path, mFV->line, mFV->fullpath, mFV->flag);
	}
}

/**
 * main - entry point to shell
 * Return: 0 on success
 */
int main(void)
{
	struct stat buff;
	struct mainFunctionVariables main_fun_var;

	initialize_variables(&main_fun_var, &buff);
	main_execution_loop(&main_fun_var, &buff);

	return (0);
}
