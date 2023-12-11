#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/**** || FOR COMMAND CHAINING ||  ****/
#define CMD_CHIAN	3
#define CMD_AND	2
#define CMD_NORMAL	0
#define CMD_OR	1

/**
 * struct list_s - the singly linked list
 *
 * @num: the field for number
 * @str: holds the string
 * @next: pointer to the address of the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - hold the arguements to pass to a function,
 * 
 * @arg: contains arguement of strings generated from getline.
 * @argv: take an array of strings from arg
 * @path: take a path for the current command of the string.
 * @argc: take the arguement counts
 * @line_count: takes the error counts
 * @err_num: takes the error code for exit() funtion.
 * @linecount_flag: count the line of input when active.
 * @fname: takes the filename of the program
 * @env: takes the local copy ofvthe linked list environ.
 * @environ: customised copy of environ variable from LL (env)
 * @history: takes the node history.
 * @alias: takes the node aliases
 * @env_changed: get active if environ variable changes.
 * @status: return the status of the latest exec'd command
 * @cmd_buf: pointer to cmd_buff, active when chaining.
 * @cmd_buf_type: takes the following, CMD_type ||, &&, ;
 * @readfd: location from which to read line input
 * @histcount: the history of the line number count.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/*** || SHELL_LOOP.C  || ***/

int loop_hsh(info_t *, char **);
int check_builtin(info_t *);
void check_cmd(info_t *);
void copy_cmd(info_t *);


/**** || LOOPHSH.C || ****/

int loop_hsh(char **);

/**** || SHELL_EXITS.C || ****/

char *_strncopy(char *, char *, int);
char *_strncats(char *, char *, int);
char *_strchar(char *, char);

/**** || SHELL REALLOC.C || ****/

char *_memeset(char *, char, unsigned int);
void ffrees(char **);
void *_reallocc(void *, unsigned int, unsigned int);


/**** || SHELL_MEMORY.C || ****/

int _free1(void **);

/**** || SHELL ERROR1.C || ****/

int _erroatoi(char *);
void print_erro(info_t *, char *);
int print_de(int, int);
char *convert_nums(long int, int, int);
void del_comments(char *);

/**** || SHELL BUILTIN1.C || ****/

int _my_historys(info_t *);
int _my_aliases(info_t *);
int unset_aliases(info_t *, char *);
int print_aliases(list_t *);
int set_aliases(info_t *, char *);


/**** || SHELL_GETINFO.C || ****/

void set_the_info(info_t *, char **);
void clear_the_info(info_t *);
void free_the_info(info_t *, int);


/**** || SHELL_VARS.C  || ****/

int isa_chain(info_t *, char *, size_t *);
void find_chain(info_t *, char *, size_t *, size_t, size_t);
int restore_alias(info_t *);
int restore_vars(info_t *);
int restore_string(char **, char *);

#endif
