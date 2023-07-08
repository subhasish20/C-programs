#include<stdio.h>
void main()
{
    char ch;
    FILE *fp;
    fp = fopen("bcaa.txt","w");
    printf("enter a character :");
    scanf("%c",&ch);
    putc(ch,fp);
    fclose(fp);
    fp = fopen("bcaa.txt","r");
    ch = getc(fp);
    printf("the value stored is :%c",ch);
    fclose(fp);   
}

