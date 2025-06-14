#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct{
    int key;
}element;

typedef struct{
    element heap[SIZE];
    int heap_size;
}HeapType;

void insert_max_heap(HeapType *h, element item){
    int i;
    i = ++(h->heap_size);

    while((i != 1) && (item.key > h->heap[i/2].key)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType *h){
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent=1;
    child=2;
}

void heap_sort(element a[], int n){
    int i;
    HeapType *h;

    h = create();
    init(h);
    for(i = 0; i < n; i++)
        insert_max_heap(h, a[i]);
    for(i = (n-1); i >= 0; i--)
        a[i] = delete_max_heap(h);

    free(h);
}

#define SIZE 8
int main(){
    int i;
    element list[SIZE] = {23,56,11,9,56,99,27,34};
    heap_sort(list, SIZE);
    for(i=0;i<SIZE;i++)
        printf("%d ", list[i].key);
    printf("\n");
    return 0;
}