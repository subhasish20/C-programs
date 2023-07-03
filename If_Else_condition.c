#include<stdio.h>
#include<conio.h>
/*if else re jadoi gote no hue tahela
 onyo ta heba*/

void main()
{
     int age;
     printf("Enter your age :");
     scanf("%d",&age);

     if (age > 18)
     { 
         //jadi age 18 ru odhika hela 
        printf(" adult\n");
        printf(" can vote\n");
        printf(" can drive\n");
     }
     else{
        //jadi age 18 ru odhika no hela thahele
        printf(" not adult\n");
        printf(" can not vote\n");
        printf(" can not drive\n");
     }
     printf("thank you\n");
     getch();
     
}