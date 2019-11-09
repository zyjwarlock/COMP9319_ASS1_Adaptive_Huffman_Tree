#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "BTtree.h"

typedef struct {

    int value;
    Tree *tree;

} Huffman;

typedef struct {
    int len;
    unsigned char ch;
    Node *node;
    int flag;
} Leaf;

Huffman *huffman(Token *token, int n);

Huffman huffman_tree;

Leaf *getLeaf(char *ch, Node *root);

void PreOrder(Node *node);

void InOrder(Node *node, char *code);

int getHeight(Tree *tree);