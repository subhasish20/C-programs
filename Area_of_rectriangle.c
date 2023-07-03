#include<stdio.h>
#include<conio.h>
void main()
{
    int a,b;
    printf("enter the value of length");
    scanf("%d",&a);

    printf("enter the value of width");
    scanf("%d",&b);
    int area;
    area = a*b;
    printf("the area of the rectriangle is : %d",area);
    getch();
}