#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    char x[64];
    srand(time(0));
    long *ptr = (long *)x;
    for (int i = 0; i < 8; i++)
    {
        *ptr = (rand() + 922337203685477587) % 922337203685477587;
        ptr++;
    }
    for (int i = 0; i < 8; i++)
    {
        printf("%lu\n", *(long *)(x + 8 * i));
    }
}