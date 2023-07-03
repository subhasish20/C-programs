#include<stdio.h>
#include<conio.h>

void main()
{
    int a,b,c;
    printf("enter two number  :");
    scanf("%d%d",&a,&b);
    c=a|b;
    printf("after bitwise operation :%b",c);
    getch();
}