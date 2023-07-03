#include<stdio.h>
#include<conio.h>
void main()
{
    int day;
    printf("enter day(1-7) :");
    scanf("%d",&day);

    switch(day)
    {
        case 1:printf("monday \n");
        break;
        case 2:printf("tuesday \n");
        break;
        case 3:printf("weddnesday \n");
        break;
        case 4:printf("thursday \n");
        break;
        case 5:printf("saturday \n");
        break;
        case 6:printf("saturday \n");
        break;
        case 7:printf("sunday \n");
        break;
        default : printf("not a valid day");
    }
getch();

}