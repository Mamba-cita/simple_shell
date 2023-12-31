Welcome to the Simple Shell project! This is a minimalist shell implementation in C that supports both interactive and non-interactive modes. Here is all the information on compilation, testing, and how to use the included test suite.

## 🛠️ Compilation

**** Compile the shell using the following command:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


## 🛠️ Testing
## Interactive Mode
Run the shell in interactive mode:

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

## Non-Interactive Mode

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
