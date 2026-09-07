#include<stdio.h>
#include<conio.h>
void main()
{
    int a,i,sum=0;
    printf("enter a number :");
    scanf("%d",&a);

    for (int i=1; i<=a; i++)
    {
        sum+=i;
    }
    printf("sum is : %d",sum);
    
}