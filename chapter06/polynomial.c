#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode{
    int coef;
    int expon;
    struct ListNode *link;
}ListNode;

typedef struct ListType{
    int size;
    ListNode *head;
    ListNode *tail;
}ListType;

void error(){
    fprintf(stderr, "메모리 할당 오류\n");
    exit(1);
}

ListType *create(){
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = NULL;
    plist->tail = NULL;
    return plist;
}

void insert_last(ListType *plist, int coef, int expon){
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if(temp == NULL) error("메모리 할당 오류");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    if(plist->tail == NULL)
        plist->head = plist->tail = temp;
    else{
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}

void poly_print(ListType *plist){
    ListNode *p = plist->head;
    printf("polynomial = ");
    for(;p;p = p->link)
        printf("%dx^%d + ", p->coef, p->expon);
    printf("\n");
}

void poly_add(ListType *plist1, ListType *plist2, ListType *plist3){
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int sum;

    while(a && b){
        if(a->expon == b->expon){
            sum = a->coef + b->coef;
            if(sum != 0) insert_last(plist3, sum, a->expon);
            a = a->link; b = b->link;
        }else if(a->expon > b->expon){
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }else{
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    for(; a != NULL; a = a->link)
        insert_last(plist3, a->coef, a->expon);
    for(; b != NULL; b = b->link)
        insert_last(plist3, b->coef, b->expon);
}

int main(){
    ListType *list1, *list2, *list3;

    list1 = create();
    list2 = create();
    list3 = create();

    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);

    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 10, 6);

    poly_print(list1);
    poly_print(list2);

    poly_add(list1, list2, list3);
    poly_print(list3);

    free(list1);
    free(list2);
    free(list3);
}