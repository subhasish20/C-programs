#include<stdio.h>
#include<conio.h>
void main()
{
    int n,r,sum=0,t;
    printf("enter a number : ");
    scanf("%d",&n);
    t=n;
    while (n>0)
    {
        r=n%10;
        sum=(sum*10)+r;
        n=n/10;
    }

    if (t==sum)
    {
        printf("palindrome ");
    }
    else
    {
        printf("not palindrome");
    }  
getch();   
}