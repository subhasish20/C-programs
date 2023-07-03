#include<stdio.h>
#include<conio.h>
void main()
{
    int a,b;
    printf("enter two number for swipping");
    scanf("%d%d",&a,&b);
    printf("before swipping :\n");
    printf("the value of a=%d  & b=%d",a,b);
    a=a+b;
    b=a-b;
    a=a-b;
    printf("after swipping : \n");
    printf("the value of a = %d & b= %d", a,b);
    getch();

}