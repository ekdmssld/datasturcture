#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define BUCKET 10
#define DIGIT 4
#define SIZE 10
typedef struct QueueType{
    int items[MAX];
    int front, rear;
}QueueType; 

void init_queue(QueueType *q){
    q->front = q->rear = 0;
}

int is_empty(QueueType *q){
    return q->front == q->rear;
}

void enqueue(QueueType *q, int item){
    if((q->rear + 1) % MAX == q->front)
        return;
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX;
}

int dequeue(QueueType *q){
    if(is_empty(q))
        return -1;
    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return item;
}

void radix_sort(int list[], int n){
    int i, b, d, factor = 1;
    QueueType queues[BUCKET];

    for(b = 0; b < BUCKET; b++)
        init_queue(&queues[b]);

    for(d = 0; d < DIGIT; d++){
        for(i = 0; i < n; i++){
            b = (list[i] / factor) % BUCKET;
            enqueue(&queues[b], list[i]);
        }
        for(b = 0, i = 0; b < BUCKET; b++){
            while(!is_empty(&queues[b])){
                list[i++] = dequeue(&queues[b]);
            }
        }
        factor *= BUCKET;
    }
}

int main(){
    int list[SIZE], i;
    srand(time(NULL));
    for(i = 0; i < SIZE; i++)
        list[i] = rand()%100;
    radix_sort(list, SIZE);
    for(i = 0; i < SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");
    return 0;
}