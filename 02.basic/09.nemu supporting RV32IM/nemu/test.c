#include<stdio.h>

int main(void)
{
    int a = 5000;
    int b = -5000;
    printf("%d\n", (__uint32_t)a < (__uint32_t)b);
    return 0;
}