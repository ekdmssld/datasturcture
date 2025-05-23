#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListType
{
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

void error(const char *message)
{
    fprintf(stderr, "오류: %s\n", message);
    exit(1);
}

ListType *create()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

void insert_last(ListType *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if (temp == NULL)
        error("메모리 할당 오류");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    if (plist->tail == NULL)
    {
        plist->head = plist->tail = temp;
    }
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}
void poly_print(ListType *plist)
{
    ListNode *p = plist->head;
    printf("polynomial = ");
    for (; p; p = p->link)
    {
        printf("%d ^ %d + ", p->coef, p->expon);
    }
    printf("\n");
}
void poly_add(ListType *plist1, ListType *plist2, ListType *plist3)
{
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int sum;

    while (a && b)
    {
        if (a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if (sum != 0)
                insert_last(plist3, sum, a->expon);
            a = a->link;
        }
        else if (a->expon > b->expon)
        {
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    for (; a; a = a->link)
        insert_last(plist3, a->coef, a->expon);
    for (; b; b = b->link)
        insert_last(plist3, b->coef, b->expon);
}

int main()
{
    ListType *plist1 = create();
    ListType *plist2 = create();
    ListType *plist3 = create();

    insert_last(plist1, 3, 12);
    insert_last(plist1, 2, 8);
    insert_last(plist1, 1, 0);

    insert_last(plist2, 8, 12);
    insert_last(plist2, -3, 10);
    insert_last(plist2, 10, 6);

    poly_print(plist1);
    poly_print(plist2);

    poly_add(plist1, plist2, plist3);
    poly_print(plist3);

    free(plist1);
    free(plist2);
    free(plist3);

    return 0;
}