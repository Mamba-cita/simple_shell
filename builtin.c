#include "linux.h"
/**
 * navdir - function changes the current working
 * directory to the specified path.
 * @path_dirname: Path to the current working directory.
 *
 * Description: function changes the current working
 * directory to the specified path.
 */
void navdir(char *path_dirname)
{
	if (path_dirname == NULL)
		chdir(getenv("HOME"));
	else if (strcmp(path_dirname, "-") == 0)
	{
		char *oldpwd = getenv("OLDPWD");

		if (oldpwd != NULL)
		{
			printf("%s\n", oldpwd);
			chdir(oldpwd);
			setenv("OLDPWD", getcwd(NULL, 0), 1);
		}
		else
			fprintf(stderr, "OLDPWD not set\n");
	}
	else
	{
		char *cur_dir = getcwd(NULL, 0);

		chdir(path_dirname);
		setenv("OLDPWD", cur_dir, 1);
		free(cur_dir);
	}
}
/**
 * myexit - This function exits the shell.
 * @dir_exit: Pointer the exit argument provided.
 *
 * Description: Function exits the shell.
 */
void myexit(char *dir_exit)
{
	if (dir_exit != NULL)
		exit(atoi(dir_exit));
	else
		exit(0);
}

/**
 * envir - This function prints all the environment variables.
 *
 * Description: - This function prints all the environment variables.
 * Return:  1 if successful.
 */
int envir(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}
