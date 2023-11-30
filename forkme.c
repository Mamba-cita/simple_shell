#include <stdio.h>
#include <unistd.h>

void forkme(void) {
    // Your forkme function implementation goes here
}

int main(void) {
    pid_t pid;
    printf("Hey Tomi\n");

    pid = fork();

    if (pid == -1) {
        perror("Error in fork function");
        return 1;
    }

    if (pid > 0) {
        // This is the parent process
        printf("This is the parent process\n");
    } else if (pid == 0) {
        // This is the child process
        printf("This is the child process\n");
    }

    printf("Passed\n");
    return 0;
}
