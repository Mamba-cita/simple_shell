#ifndef LINUX_H
#define LINUX_H

/* Parsed commands representation: */
#define EXEC 1
/* #define REDIR 2 */
#define LIST 4 /* Handle Sequencing in case of use of ; */
#define BACK 5
#define MAXARGS 10
extern char **environ; /* For environment variable 'env' */

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

/* close, Plus other system calls */
#include <unistd.h>

/* fprintf, printf */
#include <stdio.h>

/* malloc, free */
#include <stdlib.h>

/*String handlers*/
#include <string.h>

/**
 * struct func - Basic commands.
 * @type: Type of command: EXEC, LIST, or BACK.
 *
 * Description: Represents a basic command with a
 * field indicating the command type.
 */
struct func
{
	int type;
};

/**
 * struct execfunc - Executable function.
 * @type: Type of command: EXEC.
 * @argv: Array of command arguments.
 * @eargv: Array of environment arguments.
 *
 * Description: Represents an executable command with fields for
 * command arguments (argv) and environment arguments (eargv).
 */
struct execfunc
{
	int type;
	char *argv[MAXARGS], *eargv[MAXARGS];
};

/**
 * struct col_list_func - List function.
 * @left: Pointer to the left subcommand.
 * @right: Pointer to the right subcommand.
 * @type: Type of command: LIST
 * Description: Struct representing a LIST function.
 */
struct col_list_func
{
	int type;
	struct func *left;
	struct func *right;
};

/**
 * struct revers_col - Back Function.
 * @type: Type of command: BACK
 * @func: Pointer to the sub_fun_col to run in the background
 *
 * Description: Represents a background command for the sub_fun_col
 * to run in the background (func).
 */
struct revers_col
{
	int type;
	struct func *func;
};

/*Function prototypes here: */
int get_func(char *buffer, int nbuffer);
int fork_func(void);
void panicerror(char *s);
void run_func(struct func *func);
void get_cmd(char *command_name, char **argv);
void child_fork_wait(struct func *func);
void exec_cmd(char *full_path, char **argv);
struct func *execfunc(void);
struct func *col_list_func(struct func *left, struct func *right);
struct func *revers_col(struct func *sub_func);
struct func *parseline(char **ps, char *es);
struct func *parseexec(char **ps, char *es);
struct func *parseblock(char **ps, char *es);
int is_whitespace_or_symbol(char c);
int gettoken(char **ps, char *es, char **q, char **eq);
int peek(char **ps, char *es, char *toks);
struct func *parse_func(char *s);
struct func *null_char(struct func *func);

/*Built in commands Function Prototypes: */
void navdir(char *path_dirname);
int envir(void);
void myexit(char *dir_exit);

#endif
