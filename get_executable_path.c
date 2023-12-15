#include "shellheader.h"
/**
 * findExecutablePath - searches directories in PATH variable for command
 * @command: to search for
 * @resultPath: full path of command to execute
 * @searchPath: full PATH variable
 * Return: pointer to full_path
 */
char *findExecutablePath(char *command, char *resultPath, char *searchPath)
{
	struct findExecutablePathVariables fepv;

	fepv.commandLength = _stringlen(command);
	fepv.originalSearchPathLength = _stringlen(searchPath);
	fepv.searchPathCopy = malloc(sizeof(char) *
						(fepv.originalSearchPathLength + 1));
	if (fepv.searchPathCopy == NULL)
	{
		handle_errors(3);
		return (NULL);
	}
	_stringcpy(fepv.searchPathCopy, searchPath);
	fepv.dirToken = strtok(fepv.searchPathCopy, ":");
	if (fepv.dirToken == NULL)
		fepv.dirToken = strtok(NULL, ":");
	while (fepv.dirToken != NULL)
	{
		fepv.searchPathLength = _stringlen(fepv.dirToken);
		resultPath = malloc(sizeof(char) * (fepv.searchPathLength
											+ fepv.commandLength + 2));
		if (resultPath == NULL)
		{
			handle_errors(3);
			return (NULL);
		}
		_stringcpy(resultPath, fepv.dirToken);
		resultPath[fepv.searchPathLength] = '/';
		_stringcpy(resultPath + fepv.searchPathLength + 1, command);
		resultPath[fepv.searchPathLength + fepv.commandLength + 1] = '\0';
		if (access(resultPath, X_OK) != 0)
		{
			free(resultPath);
			resultPath = NULL;
			fepv.dirToken = strtok(NULL, ":");
		}
		else
			break;
	}
	free(fepv.searchPathCopy);
	return (resultPath);
}

/**
 * _getenv - gets an environment variable
 * @name: environment variable to get
 * Return: pointer to environment variable or NULL if there is no match
 */
char *_getenv(const char *name)
{
	struct getenvVariables gv;

	gv.environ_length = 0;
	while (environ[gv.environ_length] != NULL)
		gv.environ_length++;
	gv.env_cpy = NULL;
	gv.env_cpy = cpy_env(gv.env_cpy, gv.environ_length);

	gv.length = _stringlen((char *)name);
	gv.i = 0;
	while (gv.env_cpy[gv.i] != NULL)
	{
		gv.variable = gv.env_cpy[gv.i];
		gv.compare = _stringncmp((char *)name, gv.variable, gv.length);
		if (gv.compare == 1)
		{
			gv.value = strtok(gv.variable, "=");
			gv.value = strtok(NULL, "\n ");
			if (gv.value == 0)
			{
				handle_errors(4);
				exit(EXIT_FAILURE);
			}
			gv.path_length = _stringlen(gv.value);
			gv.path = malloc(sizeof(char) * gv.path_length + 1);
			if (gv.path == NULL)
			{
				handle_errors(3);
				return (NULL);
			}
			gv.path = _stringcpy(gv.path, gv.value);
			free_double(gv.env_cpy, gv.environ_length);
			return (gv.path);
		}
		gv.i++;
	}
	return (NULL);
}

/**
 * cpy_env - copies environment variable
 * @env_cpy: pointer to copy of environment variable
 * @env_len: length of environment variable
 * Return: double pointer to copy of environment variable
 */
char **cpy_env(char **env_cpy, unsigned int env_len)
{
	char *variable;
	unsigned int variable_length;
	unsigned int i;

	env_cpy = malloc(sizeof(char **) * (env_len));
	if (env_cpy == NULL)
	{
		handle_errors(3);
		return (NULL);
	}

	i = 0;
	while (i < env_len)
	{
		variable = environ[i];
		variable_length = _stringlen(variable);

		env_cpy[i] = malloc(sizeof(char) * variable_length + 1);
		if (env_cpy[i] == NULL)
		{
			handle_errors(3);
			return (NULL);
		}
		_stringcpy(env_cpy[i], environ[i]);
		i++;
	}
	return (env_cpy);
}

/**
 * customTokenizer - tokenizes string by using "\n\t\r"
 * @input: user input
 * Return: pointer to array of string after tokenization
 */

char **customTokenizer(char *input)
{
	char **tokens;
	char *token;
	unsigned int i = 0;

	tokens = malloc(BUFFER * sizeof(char *));
	if (tokens == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, "\n\t\r ");

	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, "\n\t\r ");
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_command - function for child process
 * @fullpath: full path of executable
 * @tokens: tokenized user input
 * Return: 0 on success
 */
int execute_command(char *fullpath, char **tokens)
{
	struct execute_commandVariables ecv;

	ecv.envp = environ;

	ecv.child_pid = fork();
	if (ecv.child_pid == -1)
	{
		handle_errors(1);

		exit(EXIT_FAILURE);
	}
	if (ecv.child_pid == 0)
	{
		ecv.execve_status = execve(fullpath, tokens, ecv.envp);

		if (ecv.execve_status == -1)
			return (-1);
	}
	else
		wait(&ecv.status);

	return (0);
}
