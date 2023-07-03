#include<stdio.h>
#include<conio.h>

void main()
{
    int num;
    printf("enter a number ");
    scanf("%d",&num);

    if (num%2==0)
    {
        printf("even number");
    }
    else if (num%3==0)
    {
        printf("divisible by 3");
    }
    else
    {
        printf("odd number");
    }
 
}