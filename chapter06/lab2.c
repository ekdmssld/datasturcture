#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct ListNode{
    element data;
    struct ListNode *link;
}ListNode;

ListNode *insert_first(ListNode *head, element value){
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}
ListNode *print_list(ListNode *head){
    ListNode *p;
    for(p = head; p!=NULL; p = p->link)
        printf("%d-> ", p->data);
    printf("NULL\n");
}
ListNode *search_list(ListNode *head, element x){
    ListNode *p;

    while(p != NULL){
        if(p->data == x) return p;
        p = p->link;
    }
    return NULL;
}

int main(){
    ListNode *head = NULL;

    head = insert_first(head, 10);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);
    if(search_list(head, 30) != NULL)
        printf("30을 찾았습니다.\n");
    else
        printf("30을 찾지 못했습니다.\n");

    return 0;
}