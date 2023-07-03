#include<stdio.h>
#include<conio.h>
void main()
{
    int a,b,t;
    printf("Enrer two No. for swapping :");
    scanf("%d%d",&a,&b);

    printf("Before swapping :\n");
    printf("The value of a=%d and b=%d",a,b);
    t=a;
    a=b;
    b=t;
    printf("After swapping :\n");
    printf("The value of a =%d and b=%d",a,b);
    getch();
}