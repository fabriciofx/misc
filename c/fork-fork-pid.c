#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
pid child fork() 1: 10498
ppid child fork() 1: 10497
pid child fork() 2: 10499
ppid fork() 2: 10498
*/

int
main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        printf ("ppid child fork() 1: %d\n", getppid());
        pid = fork();
        if (pid == 0) {
            printf ("ppid fork() 2: %d\n", getppid());
        } else {
            printf ("pid child fork() 2: %d\n", pid);
        }
    } else {
        printf ("pid child fork() 1: %d\n", pid);
    }

    return 0;
}
