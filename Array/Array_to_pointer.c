#include<stdio.h>
void main()
{
    int a[4]={1,2,3,4};
    int *p,*pt,*ptr,i;
    p=&a[1];
    pt=&a[2];
    ptr=&a[3];
    for ( i = 0; i<=5; i++)
    {
        printf("%d\n",&a[i]); //address of the indexes
    }
    printf("%d\n%d\n%d",p,pt,ptr); //address of all the elements       
}