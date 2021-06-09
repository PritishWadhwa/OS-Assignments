#include <stdio.h>

int main(void)
{
    FILE *fptr;
    fptr = fopen("output.txt", "w");
    char name[] = "Pritish Wadhwa";
    fprintf(fptr, "%s", name);
    fclose(fptr);
    return 0;
}