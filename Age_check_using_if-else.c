#include<stdio.h>
#include<conio.h>
void main()
{
    int age;
    printf("enter your age :");
    scanf("%d",&age);

    if (age>=18)
    {
        printf("adult \n");
    }
    else if (age >13&& age <18)
    {
        printf("teenager \n");
    }
    else
    {
        printf("chlid \n");
    }
    printf("thank you \n");      
}