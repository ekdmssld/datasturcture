// infix -> postfix 변환 및 계산 처리

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int top;
    char data[MAX][MAX]; // 문자열로 스택을 저장
} Stack;

void init(Stack *s)
{
    s->top = -1;
}

int is_empty(Stack *s)
{
    return s->top == -1;
}

int is_full(Stack *s)
{
    return s->top == MAX - 1;
}

void push(Stack *s, char *item)
{
    if (!is_full(s))
    {
        strcpy(s->data[++(s->top)], item);
    }
}

char *pop(Stack *s)
{
    if (!is_empty(s))
    {
        return s->data[(s->top)--];
    }
    return NULL;
}

char *peek(Stack *s)
{
    if (!is_empty(s))
    {
        return s->data[s->top];
    }
    return NULL;
}
// 연산자 우선 순위 설정하기
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}
// 중위 표기법 -> 후위 표기법 변환
void infix_to_postfix(char *expr, char output[][MAX], int *out_count)
{
    Stack s;
    init(&s);

    int i = 0;
    *out_count = 0;

    while (expr[i])
    {
        // 공백 건너뛰기
        if (isspace(expr[i]))
        {
            i++;
            continue;
        }

        // 숫자 또는 단항 부호
        if (isdigit(expr[i]) || ((expr[i] == '+' || expr[i] == '-') && isdigit(expr[i + 1])))
        {
            char number[MAX] = {0};
            int j = 0;
            // 부호 처리
            if (expr[i] == '+' || expr[i] == '-')
            {
                number[j++] = expr[i++];
            }
            // 숫자 처리
            while (isdigit(expr[i]))
            {
                number[j++] = expr[i++];
            }
            number[j] = '\0';
            strcpy(output[(*out_count)++], number);
            continue;
        }

        // 괄호
        if (expr[i] == '(')
        {
            char temp[2] = {expr[i], '\0'};
            push(&s, temp);
        }
        else if (expr[i] == ')')
        {
            while (!is_empty(&s) && peek(&s)[0] != '(')
            {
                strcpy(output[(*out_count)++], pop(&s));
            }
            if (!is_empty(&s))
                pop(&s); // '(' 제거
        }
        // 연산자
        else if (is_operator(expr[i]))
        {
            char op[2] = {expr[i], '\0'};
            while (!is_empty(&s) && precedence(peek(&s)[0]) >= precedence(op[0]))
            {
                strcpy(output[(*out_count)++], pop(&s));
            }
            push(&s, op);
        }

        i++;
    }
    // 스택에 남은 연산자 다 꺼내기
    while (!is_empty(&s))
    {
        strcpy(output[(*out_count)++], pop(&s));
    }
}

int eval_postfix(char postfix[][MAX], int count)
{
    Stack s;
    init(&s);

    for (int i = 0; i < count; i++)
    {
        // 숫자면 스택으로 넣기
        if (isdigit(postfix[i][0]) ||
            (postfix[i][0] == '-' && isdigit(postfix[i][1])) ||
            (postfix[i][0] == '+' && isdigit(postfix[i][1])))
        {
            push(&s, postfix[i]);
        }
        else
        {
            int b = atoi(pop(&s));
            int a = atoi(pop(&s));
            int result = 0;

            switch (postfix[i][0])
            {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            }

            char temp[MAX];
            sprintf(temp, "%d", result);
            push(&s, temp);
        }
    }

    return atoi(pop(&s));
}

int main()
{
    char expr[MAX];
    printf("수식 입력 (infix): ");
    fgets(expr, MAX, stdin);
    // 개행 제거
    expr[strcspn(expr, "\n")] = 0;

    char postfix[MAX][MAX];
    int count = 0;

    infix_to_postfix(expr, postfix, &count);

    printf("Postfix: ");
    for (int i = 0; i < count; i++)
    {
        printf("%s ", postfix[i]);
    }
    printf("\n");

    int result = eval_postfix(postfix, count);
    printf("Result: %d\n", result);

    return 0;
}
