#include "shell.h"

/**
 * isa_chain - test the chain delimiter,
 * for the current char in the buffer.
 *
 * @info: the structure parameter.
 * @buf: the buffer for the character.
 * @p: position of the current address in the buffer.
 *
 * Return: 1( if chain delimiter), otherwise 0.
 */
int isa_chain(info_t *info, char *buf, size_t *p)
{
    size_t index = *p;

    if (buf[index] == '|' && buf[index + 1] == '|')
    {
        buf[index] = 0;
        index++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[index] == '&' && buf[index + 1] == '&')
    {
        buf[index] = 0;
        index++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[index] == ';')
    {
        buf[index] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = index;
    return (1);
}

/**
 * find_chain - decide if chaining,
 * should continue based on the last result.
 * @info: the structure parameter.
 * @buf: the buffer for character.
 * @p: position of the current address in the buffer.
 * @index: starting index in the buffer
 * @len: length of the buffer
 *
 * Return: (void)
 */
void find_chain(info_t *info, char *buf, size_t *p, size_t index, size_t len)
{
    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[index] = 0;
            *p = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[index] = 0;
            *p = len;
        }
    }
}
