#include "linux.h"

/**
 * execfunc - Allocates and initializes an execfunc struct
 * Return: A pointer to the newly allocated execfunc struct
 */
struct func *execfunc(void)
{
	struct execfunc *func;

	func = malloc(sizeof(struct execfunc));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct execfunc));
	func->type = EXEC;
	return ((struct func *)func);
}

/**
 * col_list_func - Allocates and initializes a col_list_func struct
 * @left: The left sub_fun_col
 * @right: The right sub_fun_col
 * Return: A pointer to the newly allocated col_list_func struct
 */
struct func *col_list_func(struct func *left, struct func *right)
{
	struct col_list_func *func;

	func = malloc(sizeof(struct col_list_func));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct col_list_func));
	func->type = LIST;
	func->left = left;
	func->right = right;
	return ((struct func *)func);
}

/**
 * revers_col - Allocates and initializes a revers_col struct.
 * @sub_func: The sub_fun_col to run in the background
 * Return: A pointer to the newly allocated revers_col struct
 */
struct func *revers_col(struct func *sub_func)
{
	struct revers_col *func;

	func = malloc(sizeof(struct revers_col));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct revers_col));
	func->type = BACK;
	func->func = sub_func;
	return ((struct func *)func);
}

/**
 * parse_func - Parses a shell command & constructs a corresponding func struct
 * @s: The input string containing the shell command
 * Return: A pointer to the parsed func struct
 */
struct func *parse_func(char *s)
{
	struct func *func;
	char *es;

	es = s + strlen(s);
	func = parseline(&s, es);
	peek(&s, es, "");

	if (s != es)
	{
		printf("leftovers: %s\n", s);
		panicerror("syntax");
	}
	null_char(func);
	return ((struct func *)func);
}
