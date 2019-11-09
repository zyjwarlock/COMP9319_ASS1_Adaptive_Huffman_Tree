#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "HuffmanTree.h"


Huffman *huffman(Token *token, int n){
    Huffman *huff;
    huff = (Huffman *)malloc(sizeof(Huffman)*(n));
    
    int i=0;
    for(i=0; i<n; i++){
        
        huff[i].value = token[i].value;
        huff[i].tree = (Tree *)malloc(sizeof(Tree));
        ////print("%c   %d\n", token[i].data, token[i].value);
        huff[i].tree->root = initTree(huff[i].tree, token[i]);
        //initTree(huff[i].tree, token[i]);
    }
    
    return huff;
}

void PreOrder(Node *node) {  
    if(node != NULL)  
    {  

        PreOrder(node->lChild);  
        PreOrder(node->rChild);  
    }  
}  

void InOrder(Node *node, char *code){


    if(node->flag == 1){
      
        Global_head[node->ch].code = (char *)malloc(sizeof(char)*256+1);
        strcpy(Global_head[node->ch].code, code);
        //printf("%c, %s\n", node->ch, code);
        
        return;
    }
    
    if(node != NULL){
       

        char l[strlen(code)+1];
        char r[strlen(code)+1];
        
        if(strlen(code)>0){
            strcpy(l, code);
            strcpy(r, code);
            strcat(l, "0");
            strcat(r, "1");
        }
        else{
            strcpy(l, "0");
            strcpy(r, "1");
        }

        InOrder(node -> lChild, l);
        InOrder(node -> rChild, r);
    }
}

int getHeight(Tree *tree){
    return Height(tree->root);
}



Leaf *getLeaf(char *code, Node *root){

    Leaf *leaf = (Leaf *) malloc(sizeof(Leaf));
    leaf -> flag = 0;
    Node *node = root;
    int i=0;
    for(i=0; i<=strlen(code); i++){

        if(node->flag == 1){
            leaf->ch = node->ch;
            leaf->len = i;
            leaf->node = huffman_tree.tree->root;
            leaf->flag = 1;
            //printf("=========Found %c===========\n",leaf->ch);
            break;
        }
        if(code[i]=='1'){
            node = node->rChild;
        }
        else{
            node = node->lChild;
        }
        leaf->len = i;
    }
    leaf->node = node;

    return leaf;
}

