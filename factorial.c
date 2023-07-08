#include<stdio.h>

#include<conio.h>

void main()
{
    int n,i;
    unsigned long long fact=1;
    printf(" enter a number :");
    scanf("%d",&n);
    i=1;
    while (i<=n)
    {
        fact*=i;
        i++;
    }
printf("the factorial is : %llu",fact);
getch();
}