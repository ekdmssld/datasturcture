#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "contacts.txt"

// 연락처 정보를 저장할 구조체
typedef struct {
    char name[50];
    char phone[20];
    char address[100];
} element;

// 이진 탐색 트리의 노드 정의
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* root = NULL;

// 이름 기준 비교 함수
int compare(element e1, element e2) {
    return strcmp(e1.name, e2.name);
}

// 새 노드 생성
TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 트리에 노드 삽입
TreeNode* insert_node(TreeNode* node, element key) {
    if (node == NULL) return new_node(key);
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    return node;
}

// 이름으로 연락처 탐색
TreeNode* search(TreeNode* root, element key) {
    TreeNode* p = root;
    while (p != NULL) {
        if (compare(key, p->key) == 0)
            return p;
        else if (compare(key, p->key) < 0)
            p = p->left;
        else
            p = p->right;
    }
    return p;
}

// 최소값 노드 찾기 (삭제 시 필요)
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// 노드 삭제
TreeNode* delete_node(TreeNode* root, element key) {
    if (root == NULL) return root;
    if (compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    else if (compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = min_value_node(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

// 괄호 형태로 트리 출력 (중위 순회)
void display(TreeNode* p) {
    if (p != NULL) {
        printf("(");
        display(p->left);
        printf("%s", p->key.name);
        display(p->right);
        printf(")");
    }
}

// 노드 수 계산
int count_nodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// 트리 높이 계산
int tree_height(TreeNode* node) {
    if (!node) return 0;
    int l = tree_height(node->left);
    int r = tree_height(node->right);
    return (l > r ? l : r) + 1;
}

// 파일에 트리 저장 (전위 순회)
void save_to_file(TreeNode* node, FILE* fp) {
    if (node) {
        fprintf(fp, "%s|%s|%s\n", node->key.name, node->key.phone, node->key.address);
        save_to_file(node->left, fp);
        save_to_file(node->right, fp);
    }
}

// 파일에서 트리 불러오기 + 포맷 문자열 확인(필드 구분자 : |, 레코드 구분자 \n)
void load_from_file() {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) return;
    element e;
    while (fscanf(fp, "%49[^|]|%19[^|]|%99[^\n]\n", e.name, e.phone, e.address) == 3) {
        root = insert_node(root, e);
    }
    fclose(fp);
}

// 메뉴 출력
void help() {
    printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****\n");
}

int main(void) {
    char command;
    element e;
    TreeNode* tmp;
    load_from_file(); // 프로그램 실행 시 자동 불러오기

    do {
        help();
        command = getchar();
        getchar(); // 엔터 제거
        switch (command) {
        case 'i':
            printf("이름: "); fgets(e.name, sizeof(e.name), stdin); e.name[strcspn(e.name, "\n")] = 0;
            printf("전화번호: "); fgets(e.phone, sizeof(e.phone), stdin); e.phone[strcspn(e.phone, "\n")] = 0;
            printf("주소: "); fgets(e.address, sizeof(e.address), stdin); e.address[strcspn(e.address, "\n")] = 0;
            root = insert_node(root, e);
            break;
        case 'd':
            printf("이름: "); fgets(e.name, sizeof(e.name), stdin); e.name[strcspn(e.name, "\n")] = 0;
            root = delete_node(root, e);
            break;
        case 's':
            printf("이름: "); fgets(e.name, sizeof(e.name), stdin); e.name[strcspn(e.name, "\n")] = 0;
            tmp = search(root, e);
            if (tmp != NULL)
                printf("이름: %s\n전화번호: %s\n 주소: %s\n", tmp->key.name, tmp->key.phone, tmp->key.address);
            else
                printf("해당 사항 없습니다.\n");
            break;
        case 'p':
            display(root);
            printf("\ncount_node: %d  tree_height: %d\n", count_nodes(root), tree_height(root));
            break;
        case 'q': {
            FILE* fp = fopen(FILENAME, "w"); // 종료 시 저장
            if (fp) {
                save_to_file(root, fp);
                fclose(fp);
            }
            break;
        }
        }
    } while (command != 'q');

    return 0;
}
