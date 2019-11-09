#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "BTtree.h"


Node *initTree(Tree *tree, Token token){

    ////printf("%c   %d\n", token.data, token.value);
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = token.value;
    node->ch = token.data;
    node->flag = 1;
    node->lChild = NULL;
    node->rChild = NULL;

    return node;

}

Node *buildTree(Tree *tree_f, Tree *tree_s){

    Node *node = (Node *)malloc(sizeof(Node));

    node->value = tree_f->root->value + tree_s->root->value;
    
    node->lChild = tree_f->root;
    node->rChild = tree_s->root;;

    return node;
}


int Height(Node *node){
    if(node==NULL){
        return 0;
    }
    else{
        int lh, rh;
        lh = Height(node -> lChild);
        rh = Height(node -> rChild);
        return 1+(lh>rh?lh:rh); 
    }
}
