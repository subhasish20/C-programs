#include<stdio.h>
#include<conio.h>
void main()
{
    int age;
    printf("enter your age :");
    scanf("%d",&age);

    age>=18 ?printf("adult \ncan vote") :printf("not adult \n");
}