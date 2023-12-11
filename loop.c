#include "shell.h"
#include "shell1.h"

/**
 * loop_shell - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int loop_shell(info_t *info, char **argv)
{
    ssize_t read_status = 0;
    int builtin_ret = 0;

    while (read_status != -1 && builtin_ret != -2)
    {
        clear_shell_info(info);
        if (interactive_mode(info))
            _puts("$ ");
        _errputchar(BUFF_FLUSH);
        read_status = get_shell_inputs(info);
        if (read_status != -1)
        {
            set_shell_info(info, argv);
            builtin_ret = check_builtin_command(info);
            if (builtin_ret == -1)
                check_shell_command(info);
        }
        else if (interactive_mode(info))
            _putchar('\n');
        free_shell_info(info, 0);
    }
    write_shell_history(info);
    free_shell_info(info, 1);
    if (!interactive_mode(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->error_num == -1)
            exit(info->status);
        exit(info->error_num);
    }
    return (builtin_ret);
}

/**
 * check_builtin_command - checks for a builtin command
 *
 * @info: it returns the structure info
 *
 * Return: -1 if builtin not found, 0 if builtin is executed successfully.
 */
int check_builtin_command(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _my_exits},
        {"env", _my_environ},
        {"help", _myhelpp},
        {"history", _myhistory},
        {"setenv", _myset_environ},
        {"unsetenv", _myunset_environ},
        {"cd", _my_cds},
        {"alias", _my_aliases},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * check_shell_command - check for a command in PATH
 *
 * @info: return an info struct
 *
 * Return: void
 */
void check_shell_command(info_t *info)
{
    char *path = NULL;
    int i, arg_count;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, arg_count = 0; info->arg[i]; i++)
        if (!is_delimiter(info->arg[i], " \t\n"))
            arg_count++;
    if (!arg_count)
        return;

    path = check_command_path(info, _get_environment(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        copy_shell_command(info);
    }
    else
    {
        if ((interactive_mode(info) || _get_environment(info, "PATH=") || info->argv[0][0] == '/') && is_shell_command(info, info->argv[0]))
            copy_shell_command(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * copy_shell_command - copy the thread to run cmd
 * @info: return info struct
 *
 * Return: (void)
 */
void fork_shell_command(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environments(info)) == -1)
        {
            free_shell_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
