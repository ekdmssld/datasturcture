#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
}TreeNode;

//    n1
// n2    n3
int main(){
    TreeNode *n1 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n2 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n3 = (TreeNode *)malloc(sizeof(TreeNode));

    n1->data = 1;
    n1->left = n2;
    n1->right = n3;

    n2->data = 2;
    n2->left = NULL;
    n2->right = NULL;

    n3->data = 3;
    n3->left = NULL;
    n3->right = NULL;

    printf("Root: %d\n", n1->data);
    printf("Left Child: %d\n", n1->left->data);
    printf("Right Child: %d\n", n1->right->data);

    free(n1);
    free(n2);
    free(n3);

    return 0;
}