#include "linux.h"
/**
 * null_char - structure for null-terminstion of strings
 * @func: Pointer to the function to be executed.
 * Return: Pointer to the function to be executed.
 *
 * Description:  function is designed to null-terminate
 * strings within a given data structure represented
 * by the struct func and its derived structures.
 */
struct func *null_char(struct func *func)
{
	int x;
	struct revers_col *bfunc;
	struct execfunc *efunc;
	struct col_list_func *lfunc;

	if (func == 0)
		return (0);
	switch (func->type)
	{
	case EXEC:
		efunc = (struct execfunc *)func;

		for (x = 0; efunc->argv[x]; x++)
			*efunc->eargv[x] = 0;
		break;

	case LIST:
		lfunc = (struct col_list_func *)func;
		null_char(lfunc->left);
		null_char(lfunc->right);
		break;

	case BACK:
		bfunc = (struct revers_col *)func;
		null_char(bfunc->func);
		break;
	}
	return (func);
}
