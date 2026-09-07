#include<stdio.h>
#include<conio.h>
void main(){
    int n,i,a[20],sum=0;
    printf("enter how many number you want to display :");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter value %d :",i+1);
        scanf("%d",&a[i]);
    }
    printf("the sum of the  numbers  are :");
    for(i=0;i<n;i++)
    {
        sum=sum+a[i];
    }
    printf("%d",sum);
}