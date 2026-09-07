#include<stdio.h>
void main()
{
    int a[20],n,i;
    printf("enter the range to  display :");

    scanf("%d",&n);


    for(i  = 0;i < n; i++){
        printf("enter the  number  :");
        scanf("%d",&a[i]);
    }
    printf("the elements  are :");
    for(i = 0;i < n;i++){
        printf("%d\t",a[i]);
    }
}