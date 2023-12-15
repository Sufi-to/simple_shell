#include "shellheader.h"
/**
 * custom_setenv - sets environment variables
 * @name: name of variable
 * @value: value of env variable
 * @overwrite: int value
 * Return: 0 on success else -1
*/
int custom_setenv(const char *name, const char *value, int overwrite)
{
	char *vars;

	if (name == NULL || name[0] == '\0')
	{
		fprintf(stderr, "setenv: Invalid variable name\n");
		return (-1);
	}
	if (strchr(name, '=') != NULL)
	{
		fprintf(stderr, "setenv: Variable name cannot contain '='\n");
		return (-1);
	}
	if (value == NULL)
	{
		fprintf(stderr, "setenv: Invalid value\n");
		return (-1);
	}
	if (!overwrite && getenv(name) != NULL)
	{
		fprintf(stderr, "setenv: Variable '%s' already exists\n", name);
		return (-1);
	}
	vars = malloc(strlen(name) + strlen(value) + 2);
	if (vars == NULL)
	{
		perror("setenv");
		return (-1);
	}
	sprintf(vars, "%s=%s", name, value);
	if (putenv(vars) != 0)
	{
		perror("setenv");
		free(vars);
		return (-1);
	}
	return (0);
}
