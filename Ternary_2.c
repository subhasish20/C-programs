#include<stdio.h>
void main ()
{
int a,b,c;
printf("Enter three numbers:");
scanf("%d%d%d",&a,&b,&c);
(a<b && a<c) ? (b>c) ? printf("b") : printf("c") : printf("a");
}