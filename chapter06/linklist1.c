#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
}ListNode;
typedef struct{
    ListNode *head;
    ListNode *tail;
    int size;
};

ListNode *insert_first(ListNode *head, element value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}
ListNode *insert(ListNode *head, ListNode *pre, element value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}
ListNode *delete_first(ListNode *head){
    ListNode *removed;
    if(head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}
ListNode *delete(ListNode *head, ListNode *pre){
    ListNode *removed;
    if(removed == NULL) return head;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}
void print_list(ListNode *head){
    ListNode *p;
    for(p = head; p!= NULL; p = p->link)
        printf("%d-> ", p->data);
    printf("NULL\n");
}
int main(){
    ListNode *head = NULL;
    for(int i = 0; i < 5; i++){
        head = insert_first(head, i);
        print_list(head);
    }
    for(int i = 0; i < 5; i++){
        head = delete_first(head);
        print_list(head);
    }
}