#include<stdio.h>
void main()
{
    int n,sum=0,temp,rem=0;
    printf("enter number :");
    scanf("%d",&n);
    temp=n;
    while (n>0)
    {
        rem=n%10;
        sum=(sum*10)+rem;
        n = n/10;
    }
    if (temp==sum)
    {
        printf("it is a palindrome number");
    }
    else
    {
        printf("it is not a palindrome number");
    }
    
    
}