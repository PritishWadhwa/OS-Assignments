/* Name: Pritish Wadhwa
   Roll_Number: 2019440 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int globalVar = 10;

void *childFn(void *vargp)
{
    while (globalVar > -90)
    {
        globalVar--;
    }
    printf("Valus from child thread: %d\n", globalVar);
}

int main(void)
{
    pthread_t thread;
    pthread_create(&thread, NULL, childFn, NULL);
    while (globalVar < 100)
    {
        globalVar++;
    }
    printf("Values from parent thread: %d\n", globalVar);
    pthread_join(thread, NULL);
    return 0;
}