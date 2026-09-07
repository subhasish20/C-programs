#include<stdio.h>
#include<conio.h>

void main()
{
    int a,b,c;
    printf("enter two numbers\n");
    scanf("%d%d",&a,&b);
    c=a&b;
    printf("after bitwise operator :%b",c);
    getch();
}