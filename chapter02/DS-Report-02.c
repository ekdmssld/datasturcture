#include <stdio.h>
#include <stdlib.h>

void error(const char *message)
{
    fprintf(stderr, "오류: %s\n", message);
    exit(1);
}

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

ListType *create()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    if (plist == NULL)
        error("리스트 생성 오류");
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

void insert(ListType *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if (temp == NULL)
        error("메모리 할당 오류");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    // 첫 노드거나 가장 앞에 들어가야 할 경우
    if (plist->head == NULL || plist->head->expon < expon)
    {
        temp->link = plist->head;
        plist->head = temp;
        if (plist->tail == NULL)
            plist->tail = temp;
    }
    else
    {
        ListNode *prev = NULL;
        ListNode *curr = plist->head;
        while (curr != NULL && curr->expon > expon)
        {
            prev = curr;
            curr = curr->link;
        }
        temp->link = curr;
        if (prev != NULL)
            prev->link = temp;
        if (curr == NULL)
            plist->tail = temp; // 새 노드가 끝에 추가된 경우
    }

    plist->size++;
}

void poly_print(ListType *plist)
{
    ListNode *p = plist->head;
    printf("polynomial = ");
    while (p)
    {
        printf("%d ^ %d", p->coef, p->expon);
        if (p->link != NULL)
            printf(" + ");
        p = p->link;
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
                insert(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if (a->expon > b->expon)
        {
            insert(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insert(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    for (; a; a = a->link)
        insert(plist3, a->coef, a->expon);
    for (; b; b = b->link)
        insert(plist3, b->coef, b->expon);
}

void delete_all(ListType *plist)
{
    ListNode *p = plist->head;
    while (p != NULL)
    {
        ListNode *temp = p;
        p = p->link;
        free(temp);
    }
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

int main()
{
    ListType *plist1 = create();
    ListType *plist2 = create();
    ListType *plist3 = create();

    // insert() 사용 - 무작위 순서 삽입
    insert(plist1, 1, 0);
    insert(plist1, 3, 12);
    insert(plist1, 2, 8);

    insert(plist2, 10, 6);
    insert(plist2, -3, 10);
    insert(plist2, 8, 12);

    poly_print(plist1);
    poly_print(plist2);

    poly_add(plist1, plist2, plist3);
    poly_print(plist3);

    // 모든 노드 제거
    delete_all(plist1);
    delete_all(plist2);
    delete_all(plist3);
    free(plist1);
    free(plist2);
    free(plist3);

    return 0;
}
