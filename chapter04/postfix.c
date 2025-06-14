#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef char element;
typedef struct {
    element data[MAX];
    int top;
}StackType;

void init_stack(StackType *s){
    s->top = -1;
}
int is_empty(StackType *s){
    return s->top == -1;
}
int is_full(StackType *s){
    return (s->top == (MAX -1));
}
void push(StackType *s, element item){
    if(is_full(s)){
        fprintf(stderr, "스택 포화 오류");
        return;
    }else s->data[++(s->top)] = item;
}
element pop(StackType *s){
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러");
        exit(1);
    }else return s->data[(s->top)--];
}
element peek(StackType *s){
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러");
        exit(1);
    }else return s->data[(s->top)];
}
int eval(char exp[]){
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    for(i=0;i<len;i++){
        ch=exp[i];
        if(ch!='+' && ch != '-' && ch!='*' && ch!='/'){
            value = ch-'0';
            push(&s, value);
        }else{
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch){
                case '+':   push(&s, op1 + op2); break;
                case '-':   push(&s, op1 - op2); break;
                case '*':   push(&s, op1 * op2); break;
                case '/':   push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}
int main(){
    int result;
    printf("후위 표기식은 82/3-32*+\n");
    result = eval("82/3-32*+");
    printf("%d\n", result);
    return 0;
}