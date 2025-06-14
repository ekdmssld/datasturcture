#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

//       +
//   *        +
//  1   4    16   25
TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, NULL, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {'*', &n1, &n2};
TreeNode n6 = {'+', &n3, &n4};
TreeNode n7 = {'+', &n5, &n6};
TreeNode *root = &n7;

int evaluate(TreeNode *root){
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    else{
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        printf("%d %c %d\n ", op1, root->data, op2);
        switch(root->data){
            case '+': return op1 + op2;
            case '-': return op1 - op2;
            case '*': return op1 * op2;
            case '/': return op1 / op2;
            default: return 0; // 잘못된 연산자 처리
        }
    }
    return 0;
}

int main(){
    printf("수식의 값 = %d", evaluate(root));
    return 0;
}