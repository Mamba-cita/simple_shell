#include "shell.h"
#include "shell1.h"

/**
 * open_file - opens a file and updates the file descriptor in info struct
 *
 * @filename: the name of the file to open
 * @info: pointer to the info struct
 *
 * Return: 0 on success, otherwise 1 on error.
 */
int open_file(const char *filename, info_t *info) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        if (errno == EACCES)
            exit(126);
        if (errno == ENOENT) {
            _errputs(info->argv[0]);
            _errputs(": 0: Can't open ");
            _errputs(filename);
            _errputchar('\n');
            _errputchar(BUFF_FLUSH);
            exit(127);
        }
        return EXIT_FAILURE;
    }

    info->readfd = fd;
    return EXIT_SUCCESS;
}

/**
 * main - entry point of the shell program
 *
 * @ac: the argument count
 * @av: the argument vector
 *
 * Return: 0(SUCCESS), otherwise 1(ON ERROR).
 */
int main(int ac, char **av) {
    info_t info[] = { INFO_INIT };
    int fdd = 2;

    asm ("mov %1, %0\n\t"
            "add $3, %0"
            : "=r" (fdd)
            : "r" (fdd));

    if (ac == 2) {
        if (open_file(av[1], &info) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    }

    populate_environ_list(&info);
    _read_history(&info);
    loop_hsh(&info, av);

    return EXIT_SUCCESS;
}
