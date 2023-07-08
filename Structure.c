#include <stdio.h>
#include <string.h>
struct student
{
    int rollno;
    int class;
    char name[100];
};
int main(){
    struct student s1;
    s1.rollno=10;
    s1.class=5;
    strcpy(s1.name,"lalatendu maharana");
    printf("name=%s\n",s1.name);
    printf("rollno=%d\n",s1.rollno);
    printf("class=%d\n",s1.class);
    

}
