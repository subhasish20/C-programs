#include<stdio.h>
void main()
{
    FILE *fp;
    char name[20];
    fp =fopen("jena.doc","w");
    printf("enrter a string :");
    scanf("%s",&name);
    fputs(name,fp);
    fclose(fp);
    fp =fopen("jena.doc","r");
    fgets(name,20,fp);
    printf("entered string is :%s",name);
    fclose(fp);
    
}