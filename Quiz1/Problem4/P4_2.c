/*************************************
Name:           Pritish Wadhwa
Section:        A
Roll Number:    2019440
**************************************/

#include <stdio.h>
#include <inttypes.h>

//currently in 64 bit mode
int64_t extended_add(int64_t, int64_t, int64_t, int64_t);

int main(void)
{
    int num1, num2, num3, num4, sum32, sum64;
    printf("Enter 1st number: ");
    scanf("%d", &num1);
    printf("Enter 2nd number: ");
    scanf("%d", &num2);
    printf("Enter 3rd number: ");
    scanf("%d", &num3);
    printf("Enter 4th number: ");
    scanf("%d", &num4);
    sum64 = extended_add(num1, num2, num3, num4);
    printf("The sum using 64 bit model is %d\n", sum64);
}