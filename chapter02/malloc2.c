#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentTag{
    char name[10];
    int age;
    double gpa;
}student;

int main(){
    student *s;
    s=(student *)malloc(sizeof(student));
    if(s==NULL){
        fprintf(stderr, "메모리 존나 부족");
        exit(1);
    }
    strcpy(s->name, "PARK");
    s->age = 20;
    free(s);
    return 0;
}