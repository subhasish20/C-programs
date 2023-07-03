#include<stdio.h>
#include<conio.h>
#include<math.h>
void main()
{
    int x;
    printf("Enter a number :");
    scanf("%d",&x);
    printf("%d", x % 2 == 0);
    getch();
}