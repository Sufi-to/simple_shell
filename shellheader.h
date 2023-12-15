#ifndef SHELLHEADER_H
#define SHELLHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER 1024
#define TRUE 1

#define EM "Unable to malloc space\n"
#define EF "Unable to fork and create child process\n"
#define EP "No such file or directory\n"
extern char **environ;

/**
 * struct mainFunctionVariables - struct for main variables
 * Description: stores variable used for environment process
 * @line: input line
 * @path: path to the executable
 * @fullpath: fullpath to the executable
 * @tokens: double pointer for tokenized strings
 * @flag: int for updating flag
 * @builtin_status: status of command if builtin or not
 * @child_status: go to the child process
*/
struct mainFunctionVariables
{
	char *line;
	char *path;
	char *fullpath;
	char **tokens;
	int flag;
	int builtin_status;
	int child_status;
};

/**
 * struct getenvVariables - environment variables storage
 * @env_cpy: copy of environment variables
 * @variable: env variables
 * @value: value of env variable
 * @path: path to the executable
 * @compare: compare status
 * @path_length: length of path
 * @environ_length: length of env variable
 * @length: length of var
 * @i: int number
*/
struct getenvVariables
{
	char **env_cpy;
	char *variable;
	char *value;
	char *path;
	int compare;
	unsigned int path_length;
	unsigned int environ_length;
	unsigned int length;
	unsigned int i;

};
/**
 * struct findExecutablePathVariables - struct for finding executable path
 * @commandLength: length of the command
 * @searchPathLength: length of the path to be searched
 * @originalSearchPathLength: length of path original
 * @searchPathCopy: copy of the path to be searched
 * @dirToken: directory token
*/
struct findExecutablePathVariables
{
	unsigned int commandLength;
	unsigned int searchPathLength;
	unsigned int originalSearchPathLength;
	char *searchPathCopy;
	char *dirToken;
};

/**
 * struct execute_commandVariables - struct for exec variables
 * @child_pid: child pid_t
 * @status: status of the child
 * @execve_status: status of execve functiong
 * @envp: environment variable
*/
struct execute_commandVariables
{
	pid_t child_pid;
	int status;
	int execve_status;
	char **envp;
};
/**
 * struct builtin_executeVariables - struct for builtin exec variables
 * @length: length of builtin
 * @status: status of builtin
 * @num: num of execve
 * @i: counter
*/
struct builtin_executeVariables
{
	int status;
	unsigned int length;
	unsigned int num;
	unsigned int i;
};


/**
 * struct built_s - linked list of builtins
 * @name: name of builtin
 * @p: pointer to function
 *
 * Description: struct for builtin functions.
**/
typedef struct built_s
{
	char *name;
	int (*p)(void);
} built_s;

void prompt_sh(int fd, struct stat buff);
char *_getlinefromstd(FILE *inp);
char **customTokenizer(char *input);

char *findExecutablePath(char *command, char *resultPath, char *searchPath);
int execute_command(char *fullpath, char **tokens);
void handle_errors(int error);


void _puts(char *s);
int _stringlen(char *s);
int _strcmp(char *name, char *var, unsigned int len);
int _stringncmp(char *name, char *str, unsigned int len);
char *_stringcpy(char *dest, char *src);


int print_shell_env(void);

int builtin_execute(char **tokens);
int shell_num_builtins(built_s builtin[]);


char *_getenv(const char *name);
char **cpy_env(char **env_cpy, unsigned int env_len);

void free_all(char **tokens, char *path, char *line, char *fullpath, int flag);
void free_double(char **arr, unsigned int len);

void main_execution_loop(struct mainFunctionVariables *mFV, struct stat *buff);
void initialize_variables(struct mainFunctionVariables *mFV,
											struct stat *buff);
int custom_setenv(const char *name, const char *value, int overwrite);

int cd_shell(struct mainFunctionVariables *mFV);

void cdCommand(char *directory);
void clearInputBuffer(void);
int exit_shell_wrapper(void);
int exit_shell(char *arg);
#endif

