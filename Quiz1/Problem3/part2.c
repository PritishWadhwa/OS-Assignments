#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    char x[64];
    srand(time(0));
    int *ptr = (int *)x;
    for (int i = 0; i < 16; i++)
    {
        *ptr = (rand() + 2147483647) % 2147483647;
        ptr++;
    }
    for (int i = 0; i < 16; i++)
    {
        printf("%u\n", *(int *)(x + 4 * i));
    }
}