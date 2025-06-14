#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
typedef struct{
    int id;
    int arrival_time;
    int service_time;
}element;

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
    if(is_full(q))
        error("큐가 포화 상태입니다.");
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = item;
}
element dequeue(QueueType *q){
    if(is_empty(q))
        error("큐가 공백 상태입니다.");
    q->front = (q->front + 1) % MAX;
    return q->data[q->front];
}

element peek(QueueType *q){
    if(is_empty(q))
        error("큐가 공백 상태입니다.");
    return q->data[(q->front + 1) % MAX];
}

int main(){
    int minutes = 60;
    int total_wait = 0, total_customers = 0, service_time = 0;
    int service_customer;
    QueueType q;

    init_queue(&q);
    srand(time(NULL));

    for(int clock = 0; clock < minutes; clock++){
        printf("현재 시각 : %d\n", clock);
        if((rand()%10 < 3)){
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&q, customer);
            printf("고객 %d가 %d분에 들어옵니다. 업무 처리 시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }
        if(service_time > 0){
            printf("고객 %d의 업무 처리중입니다. \n", service_customer);
            service_time--;
        }else{
            if(!is_empty(&q)){
                element costomer = dequeue(&q);
                service_customer = costomer.id;
                service_time = costomer.service_time;
                printf("고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d분 이었습니다.\n", costomer.id, clock, clock - costomer.arrival_time);
                total_wait += clock - costomer.arrival_time;
            }
        }
    }
    printf("전체 대기 시간 %d분\n", total_wait);
    return 0;
}