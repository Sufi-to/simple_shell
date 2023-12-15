#include "shellheader.h"

/**
 * cd_shell - Implementation of the "cd" built-in command
 * @mFV: struct containing main function variables
 * Description: This function is responsible for handling the "cd"
 * command in the simple shell. It parses the argument after "cd"
 * and calls the cdCommand function to change the current working
 * directory.
 * Return: Returns 0 to indicate successful execution of the "cd"
 * command.
 */

int cd_shell(struct mainFunctionVariables *mFV)
{
	if (mFV->tokens[1] == NULL)
	{

		cdCommand(NULL);
	}
	else
	{
		cdCommand(mFV->tokens[1]);
	}
	return (0);
}

/**
 * cdCommand - Change the current working directory based on the given
 * directory.
 * @directory: The target directory to change to.
 *
 * If the directory is NULL, interpret it as cd $HOME.
 * If the directory is "-", change to the previous directory (OLPWD).
 * Otherwise, change to the specified directory.
 *
 * Update environment variables PWD and OLDPWD accordingly.
 */
void cdCommand(char *directory)
{
	char *oldPwd;
	char *newDirectory;
	char *currentDirectory;

	if (directory == NULL)
	{
		newDirectory = getenv("HOME");
	}
	else if (strcmp(directory, "-") == 0)
	{
		newDirectory = getenv("OLDPWD");
	}
	else
	{
		newDirectory = directory;
	}
	currentDirectory = getcwd(NULL, 0);

	if (chdir(newDirectory) != 0)
	{
		perror("cd");
	}
	else
	{
		oldPwd = getenv("PWD");
		setenv("OLDPWD", oldPwd ? oldPwd : "", 1);
		setenv("PWD", currentDirectory, 1);
	}
	free(currentDirectory);
}

/**
 * handle_errors - prints errors based on case
 * @error: error number associated with perror statement
 * Return: void
 */
void handle_errors(int error)
{
	switch (error)
	{
	case 1: /* fork error */
		write(STDERR_FILENO, EF, _stringlen(EF));
		perror("Error");
		break;

	case 2: /* execve error */
		perror("Error");
		break;

	case 3: /* malloc error */
		write(STDERR_FILENO, EM, _stringlen(EM));
		break;
	case 4: /* writes empty path error to stderr */
		write(STDERR_FILENO, EP, _stringlen(EP));
		break;

	default:
		return;
	}
}

