#include<stdio.h>
#include<conio.h>

void main()
{
    int a,b,c,d;
    printf("enter four number :");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if(a>b&&a>c&&a>d)
    {
        printf("the greatest number is :%d",a);
    }
    else if (b>c&&b>d)
    {
        printf("the greayest number is :%d",b);
    }
    else if (c>d)
    {
        printf("the greatst number is :%d",c);
    }
    else
    {
        printf("the greatest number is :%d",d);
    }
    
    
    
}