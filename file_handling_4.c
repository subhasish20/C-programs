#include<stdio.h>
void main()
{
    int a;
    FILE *fp;
    fp=fopen("file1.doc","w");
    printf("enter a number :");
    scanf("%d",&a);
    putw(a,fp);
    fclose(fp);
    fp=fopen("file1.doc","r");
    a = getw(fp);
    printf("entered num :%d",a);
    fclose(fp);
    
}