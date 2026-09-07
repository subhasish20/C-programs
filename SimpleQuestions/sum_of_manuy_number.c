#include<stdio.h>
#include<conio.h>

void main()
{
    int i,n,sum=0,x;
    printf("enter how many number for addition:");
    scanf("%d",&n);
    i=1;

    while (i<=n)
    {
        printf("enter number%d:",i);
        scanf("%d",&x);
        sum=sum+x;
        i++;
    }
    printf(" sum of all number is :%d",sum);
}