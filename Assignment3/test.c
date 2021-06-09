/* Name: Pritish Wadhwa
   Roll_Number: 2019440 */
#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main() {
    long long int ctr;
	struct timeval t1, t2;
    pid_t pid;        
    long long int realtimeValue;
    printf("Enter the requires realtime value(between 0 and 30000000000): ");
    scanf("%lld", &realtimeValue);
    if((pid = fork()) == 0)
    { 
        long ret = syscall(336, getpid(), realtimeValue);
		if(ret != 0) 
        {
			printf("%s\n", strerror(ret));
			exit(ret);
		}
        gettimeofday(&t1, NULL);
        for(ctr = 0; ctr < 100000000; ctr++);
        gettimeofday(&t2, NULL);      
        printf("Execution time of child = %lf milliseconds for ctr = %lld\n", (double) (t2.tv_usec-t1.tv_usec)/1000 + (double) (t2.tv_sec-t1.tv_sec)*1000, ctr);
    }
    else if(pid > 0)
    {
        gettimeofday(&t1, NULL);
        for(ctr = 0; ctr < 10000000; ctr++);
        gettimeofday(&t2, NULL);
        printf("Execution time of parent = %lf milliseconds for ctr = %lld\n", (double) (t2.tv_usec-t1.tv_usec)/1000 + (double) (t2.tv_sec-t1.tv_sec)*1000, ctr);
		wait(NULL);
    }
    else
    {
        printf("%s\n", strerror(errno));
		exit(errno);
        return 1;
    }
    return 0;
}