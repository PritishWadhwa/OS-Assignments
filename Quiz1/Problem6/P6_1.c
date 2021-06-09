#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char firstName[] = "Pritish";
    char *secondName;
    secondName = (char *)malloc(7 * sizeof(char));
    secondName = "Wadhwa";
    printf("%s %s\n", firstName, secondName);
    return 0;
}