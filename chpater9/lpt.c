#include <stdio.h>
#include <stdlib.h>
#define MAX 200

typedef struct {
    int id;
    int avail;
}element;

typedef struct{
    element heap[MAX];
    int heap_size;
}HeapType;

HeapType *create(){
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h){
    h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item){
    int i;
    i = ++(h->heap_size);
    while((i!=1) && (item.avail < h->heap[i/2].avail)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }h->heap[i] = item;
}

element delete_min_heap(HeapType *h){
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while(child <= h->heap_size){
        if((child < h->heap_size) && (h->heap[child].avail) > h->heap[child+1].avail)
            child++;
        if(temp.avail < h->heap[child].avail) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

#define JOBS 7
#define MACHINES 3

int main(){
    int jobs[JOBS] = {8,7,6,5,3,2,1};
    element m = {0,0};
}