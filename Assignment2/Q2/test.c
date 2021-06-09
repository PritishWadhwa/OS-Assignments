/* Name: Pritish Wadhwa
   Roll_Number: 2019440 */
#include <stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(void)
{
    int id;
    char path[256];
    printf("Please enter the required PID: ");
    scanf("%d", &id);
    printf("Please enter the name of the new file required along with path: ");
    scanf("%s", path);
    long int runSyscall = syscall(335, id, path);
    printf("System call returned %ld\n", runSyscall);
    return 0;
}