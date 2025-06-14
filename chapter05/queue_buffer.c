#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    int data = 0;

    init_queue(&q);
    srand(time(NULL));

    for(int i = 0; i < 100; i++){
        if(rand() % 5 == 0)
            enqueue(&q, rand()%100);
        queue_print(&q);
        if(rand() % 10 == 0)
            data = dequeue(&q);
        queue_print(&q);
    }
    return 0;
}