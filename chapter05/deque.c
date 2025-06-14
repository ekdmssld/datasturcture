#include <stdio.h>
#include <stdlib.h>

#define MAX 5
typedef int element;
typedef struct{
    int front, rear;
    element data[MAX];
}DequeueType;

void error(const char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_deque(DequeueType *dq){
    dq->front = dq->rear = 0;
}
int is_empty(DequeueType *dq){
    return (dq->front == dq->rear);
}
int is_full(DequeueType *dq){
    return ((dq->rear + 1) % MAX == dq->front);
}
void dequeue_print(DequeueType *q){
    printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
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
void add_rear(DequeueType *dq, element item){
    if(is_full(dq))
        error("덱이 포화 상태입니다.");
    dq->rear = (dq->rear + 1) % MAX;
    dq->data[dq->rear] = item;
}
element delete_front(DequeueType *dq){
    if(is_empty(dq)){
        error("덱이 공백 상태입니다.");
    }
    dq->front = (dq->front + 1) % MAX;
    return dq->data[dq->front];
}
element get_front(DequeueType *dq){
    if(is_empty(dq))
        error("덱이 공백 상태입니다.");
    return dq->data[(dq->front + 1) % MAX];
}
void add_front(DequeueType *dq, element val){
    if(is_full(dq))
        error("덱이 포화 상태입니다.");
    dq->data[dq->front] = val;
    dq->front = (dq->front -1 + MAX) % MAX;
}
element delete_rear(DequeueType *q){
    int prev = q->rear;
    if(is_empty(q))
        error("덱이 공백 상태입니다.");
    q->rear = (q->rear -1 + MAX) % MAX;
    return q->data[prev];
}

element get_rear(DequeueType *q){
    if(is_empty(q))
        error("덱이 공백 상태입니다.");
    return q->data[q->rear];
}

int main(){
    DequeueType dq;
    init_deque(&dq);
    for(int i = 0; i < 3 ; i++){
        add_front(&dq, i);
        dequeue_print(&dq);
    }
    for(int i = 0; i < 3; i++){
        delete_rear(&dq);
        dequeue_print(&dq);
    }

    return 0;
}