#include "shell.h"

/**
 * is_executable - check if the file is an executable command
 * @info: the structure for the info
 * @path: the path pointing to the file
 *
 * Return: 1(true), 0 otherwise.
 */
int is_executable(info_t *info, char *path)
{
    struct stat file_stats;

    (void)info;
    if (!path || stat(path, &file_stats))
        return 0;

    if (file_stats.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicate_characters - always duplicates the characters
 *
 * @path_str: the path of the string.
 * @start: start the index
 * @stop: stop the index
 *
 * Return: address to the new buffer
 */
char *duplicate_characters(char *path_str, int start, int stop)
{
    static char buffer[1024];
    int i = 0, j = 0;

    for (j = 0, i = start; i < stop; i++)
        if (path_str[i] != ':')
            buffer[j++] = path_str[i];
    buffer[j] = '\0';
    return buffer;
}

/**
 * check_command_path - check the command in the string path.
 *
 * @info: the structure info
 * @path_str: the string path
 * @command: the command to find
 *
 * Return: full path(if found), otherwise (NULL)
 */
char *check_command_path(info_t *info, char *path_str, char *command)
{
    int j = 0, curr_position = 0;
    char *path;

    if (!path_str)
        return NULL;
    if ((_strlen(command) > 2) && start(command, "./"))
    {
        if (is_executable(info, command))
            return command;
    }
    while (1)
    {
        if (!path_str[j] || path_str[j] == ':')
        {
            path = duplicate_characters(path_str, curr_position, j);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_executable(info, path))
                return path;
            if (!path_str[j])
                break;
            curr_position = j;
        }
        j++;
    }
    return NULL;
}
