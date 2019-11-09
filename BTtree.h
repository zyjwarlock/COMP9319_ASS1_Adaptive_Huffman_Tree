#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Header.h"

typedef struct TreeNode {

    struct TreeNode *lChild;
    struct TreeNode *rChild;
    unsigned char ch;
    int flag;
    int value;

} Node;

typedef struct {
    Node* root;
}Tree;

Node *initTree(Tree *tree, Token token);

Node *buildTree(Tree *tree_f, Tree *tree_s);

int Height(Node *node);