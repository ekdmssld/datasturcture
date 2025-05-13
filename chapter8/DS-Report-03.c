#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "contacts.txt"

typedef struct {
    char name[50];
    char phone[20];
    char address[100];
} element;

typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* root = NULL;

int compare(element e1, element e2) {
    return strcmp(e1.name, e2.name);
}

TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* node, element key) {
    if (node == NULL) return new_node(key);
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    return node;
}

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

TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

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

void display(TreeNode* p) {
    if (p != NULL) {
        printf("(");
        display(p->left);
        printf("%s", p->key.name);
        display(p->right);
        printf(")");
    }
}

int count_nodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

int tree_height(TreeNode* node) {
    if (!node) return 0;
    int l = tree_height(node->left);
    int r = tree_height(node->right);
    return (l > r ? l : r) + 1;
}

void save_to_file(TreeNode* node, FILE* fp) {
    if (node) {
        fprintf(fp, "%s|%s|%s\n", node->key.name, node->key.phone, node->key.address);
        save_to_file(node->left, fp);
        save_to_file(node->right, fp);
    }
}

void load_from_file() {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) return;
    element e;
    while (fscanf(fp, "%49[^|]|%19[^|]|%99[^\n]\n", e.name, e.phone, e.address) == 3) {
        root = insert_node(root, e);
    }
    fclose(fp);
}

void help() {
    printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****\n");
}

int main(void) {
    char command;
    element e;
    TreeNode* tmp;
    load_from_file();

    do {
        help();
        command = getchar();
        getchar();
        switch (command) {
        case 'i':
            printf("이름: "); gets(e.name);
            printf("전화번호: "); gets(e.phone);
            printf("주소: "); gets(e.address);
            root = insert_node(root, e);
            break;
        case 'd':
            printf("이름: "); gets(e.name);
            root = delete_node(root, e);
            break;
        case 's':
            printf("이름: "); gets(e.name);
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
            FILE* fp = fopen(FILENAME, "w");
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
