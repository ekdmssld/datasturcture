#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int element;
typedef struct{
    int front;
    int rear;
    element data[MAX];
}QueueType;

void error(const char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}
void init_queue(QueueType *q){
    q->front = q->rear = 0;
}
int is_empty(QueueType *q){
    return (q->front == q->rear);
}
int is_full(QueueType *q){
    return ((q->rear + 1) % MAX == q->front);
}
void queue_print(QueueType *q){
    printf("QUEUE(front %d rear %d) = ", q->front, q->rear);
    if(!is_empty(q)){
        int i = q->front;
        do{
            i = (i+1) % MAX;
            printf("%d | ", q->data[i]);
            if(i == q->rear)
                break;
        }while(i != q->front);
    }
    printf("\n");
}

void enqueue(QueueType *q, element item){
    if(is_full(q)){
        error("큐가 포화 상태입니다.");
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = item;
}
element dequeue(QueueType *q){
    if(is_empty(q))
        error("큐가 공백 상태입니다.");
    q->front = (q->front +1) % MAX;
    return q->data[q->front];
}
element peek(QueueType *q){
    if(is_empty(q))
        error("큐가 공백 상태입니다.");
    return q->data[(q->front + 1) % MAX];
}

int main(){
    QueueType q;
    int element = 0;

    init_queue(&q);
    printf("====데이터 추가 단계 ====\n");
    while(!is_full(&q)){
        printf("정수를 입력하세요 : ");
        scanf("%d", &element);
        enqueue(&q, element);
        queue_print(&q);
    }
    printf("큐는 포화상태입니다. \n\n");

    printf("====데이터 삭제 단계 ====\n");
    while(!is_empty(&q)){
        element = dequeue(&q);
        printf("꺼내진 정수 : %d\n", element);
        queue_print(&q);
    }
    printf("큐는 공백 상태입니다. \n\n");
    return 0;
}