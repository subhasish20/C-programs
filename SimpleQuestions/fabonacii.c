#include<stdio.h>
void main()
{
    int n,a=0,b=1,c,i;
    printf("enter the range :");
    scanf("%d",&n);
    printf("the fabonacci series is :");
    for ( i = 1; i <= n; i++)
    {
        printf("%d",a);
        c=a+b;
        a=b;
        b=c;
    }
    
}