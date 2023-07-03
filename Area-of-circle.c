#include<stdio.h>
#include<conio.h>
#include<math.h>
void main()
{
    float r,area,power;
    printf("Write the radious of circle :");
    scanf("%f",&r);
    
    power=pow(r,r);
    area=3.141*power;
    printf("The area of circle is: %f",area);
    getch();
}