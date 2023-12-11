#ifndef _SHELL_H
#define _SHELL_H

#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


/*** || SYSTEM getline() FUNCTION RETURN 1 WHEN ACTIVE  || ***/

#define ACTIVE_GETLINE 0
#define ACTIVE_STRTOK 0

#define HEIST_FILE	".simple_shell_history"
#define HEIST_MAX	4096

extern char **envir;

/**** ||  FOR WRITING AND READING FROM BUFFERS || ****/

#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/*** || FOR convert_number() FUNCTION || ****/

#define CONVERTS_LOWERCASE	1
#define CONVERTS_UNSIGNED	2

/**
 * struct passinfo - hold the arguements to pass to a function.
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

/**
 * struct builtin_s - contain a string that is builtin
 * @type: take the command flag for builtin_s
 * @func: takes the related function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/*** || SHELL_PARSER.C ||***/

char *dupli_char(char *, int, int);
char *check_path(info_t *, char *, char *);
int is_cmds(info_t *, char *);


/**** || SHELL ERRORS.C || ****/

void _errputs(char *);
int _errputchar(char);
int _putfds(char c, int fd);
int _putsfds(char *str, int fd);

/**** || SHELL_STRING.C || ****/

int _strlen(char *);
int _strcmp(char *, char *);
char *start(const char *, const char *);
char *_strcat(char *, char *);

/**** || SHELL_STRING1.C || ****/

char *_strcpy(char *, char *);
char *_strdupli(const char *);
void _puts(char *);
int _putchar(char);

/**** || SHELL_TOKENIZER.C || ****/

char **_strtow(char *, char *);
char **_strtow2(char *, char);

/**** || SHELL_ATOI.C || ****/

int interactives(info_t *);
int is_deli(char, char *);
int _isalphab(int);
int _isatoi(char *);


/**** || SHELL_BUILTIN.C || ****/

int _my_exits(info_t *);
int _my_cds(info_t *);
int _myhelpp(info_t *);

/**** || SHELL_GETLINE.C || ****/

ssize_t gets_inputs(info_t *);
void sigint_handler(int);
int _getlines(info_t *, char **, size_t *);
ssize_t read_buff(info_t *, char *, size_t *)vi
ssize_t input_buff(info_t *, char **, size_t *)

/**** || SHELL_ENVIRON.C || ****/

char *_get_environ(info_t *, const char *);
int _my_environ(info_t *);
int _myset_environ(info_t *);
int _myunset_environ(info_t *);
int populate_environ_list(info_t *);

/**** || SHELL_GETENV.C || ****/

char **get_environs(info_t *);
int set_environs(info_t *, char *, char *);
int unset_environs(info_t *, char *);

/**** || SHELL_HISTORY.C || ****/

char *gets_history_files(info_t *info);
int writes_history(info_t *info);
int readd_history(info_t *info);
int built_history_list(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/**** || SHELL LISTS.C || ****/

list_t *add_nodes(list_t **, const char *, int);
list_t *add_nodes_end(list_t **, const char *, int);
int del_nodes_at_index(list_t **, unsigned int);
void free_lists(list_t **);
size_t print_lists_str(const list_t *);

/**** || SHELL_LISTS1.C || ****/

char **lists_to_string(list_t *);
list_t *nodes_start_with(list_t *, char *, char);
size_t prints_lists(const list_t *);
ssize_t get_nodes_index(list_t *, list_t *);
size_t lists_len(const list_t *);


#endif
