#include <stdio.h>
#include <inttypes.h>

int64_t add(int64_t, int64_t);

int main(void)
{
    int64_t num1, num2;
    printf("Enter Number 1: ");
    scanf("%ld", &num1);
    printf("Enter Number 2: ");
    scanf("%ld", &num2);
    int64_t sum = add(num1, num2);
    printf("The sum is: %ld\n", sum);
    return 0;
}