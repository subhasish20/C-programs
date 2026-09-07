#include<stdio.h>
#include<conio.h>
void main(){
    int i,j,range;
    printf("Enter the ragnge : ");
    scanf("%d",&range);
    for( i = range; i >= 1; i--){
        for( j = 1; j <= i; ++j){
            printf("*");
        }
        printf("\n");
    }
    for( i = 1; i <= range; i++){
        for( j = 1; j <= i; ++j){
            printf("*");
        }   
        printf("\n");
    }
}