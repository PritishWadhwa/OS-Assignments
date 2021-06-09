/* Name: Pritish Wadhwa
   Roll_Number: 2019440 */
   
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>

int globalVar = 10;

int main(void)
{
    pid_t pid;
    int stat;
    if ((pid = fork()) == 0)
    {
        while (globalVar > -90)
        {
            globalVar--;
        }
        printf("Value from the child process: %d\n", globalVar);
        exit(0);
    }
    else if (pid > 0)
    {
        while (globalVar < 100)
        {
            globalVar++;
        }
        printf("Value from the parent process: %d\n", globalVar);
        while (waitpid(pid, &stat, 0) == -1)
        {
            if (stat != EINTR)
            {
                perror("waitpid");
                return EX_SOFTWARE;
            }
        }
    }
    else
    {
        perror("fork");
        return EX_OSERR;
    }
    return 0;
}