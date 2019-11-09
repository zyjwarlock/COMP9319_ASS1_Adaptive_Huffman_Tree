#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "Coding.h"


Huffman getHuffman(Token *token, int num){

    Huffman *huff = huffman(token, num);
   

    Heap *heap = MinHeap(num);

    
    int i=0;
    for(i=0; i<num; i++){
        insertQue(heap, huff[i]);
    }



    Huffman huff_x, huff_y;

    int times = 0;
    while(getLen(heap)>1){
        
        huff_x = removeMin(heap);

        huff_y = removeMin(heap);
        
        Huffman *huff_z = (Huffman *)malloc(sizeof(Huffman));
        huff_z->value = huff_x.value+huff_y.value;
        huff_z->tree = (Tree *)malloc(sizeof(Tree));
        Node *node = buildTree(huff_x.tree, huff_y.tree);
        huff_z->tree->root = node;
        insertQue(heap, *huff_z);
    }
    //printf("%d ", heap->que[0].value);
    
    Huffman huffman_tree = removeMin(heap);
    //free(heap);//new
    return huffman_tree;
}


int encode(char *src, char *output){

    Global_head = (Head *)malloc(sizeof(Head)*256);

    int i=0;
    for (i=0; i<256; i++){
        Global_head[i].count = 0;
        //printf("%c   %d\n", i, Global_head[i].count);
    }

    //printf("%lu\n", sizeof(Global_head));
    
    if(!readFile(src)){
        printf("open src fail\n");
        return 0;
    }

    int num = 0;
    
    for(i=0; i<256; i++){
        if(Global_head[i].count > 0){
            num++;
        }
    }
    
    Token *token = (Token *)malloc(sizeof(Token)*num);

    getToken(num, token);
    
    
    huffman_tree = getHuffman(token, num);

    //free(token);
    

    InOrder(huffman_tree.tree->root, "");


    if(!writeBinary(output, src)){
        return 0;
    }

    return 1;

}

int decode(char *src, char *output){

    Global_head = (Head *)malloc(sizeof(Head)*256);

    int i=0;
    for (i=0; i<256; i++){
        Global_head[i].count = 0;
        //printf("%c   %d\n", i, Global_head[i].count);
    }

    if(!readHeader(src)){
        return 0;
    }


    int num = 0;
    
    int sumValue = 0;

    for(i=0; i<256; i++){
        if(Global_head[i].count > 0){
            num++;
            sumValue+=Global_head[i].count;
            //printf("%c %d\n",i, Global_head[i].count);
        }
    }


    Token *token = (Token *)malloc(sizeof(Token)*num);
    
    getToken(num, token);

    huffman_tree = getHuffman(token, num);

    //PreOrder(huffman_tree.tree->root);

    //free(token);

    printf("work\n");

    if(!writeFile(output, src, sumValue)){
        return 0;
    }

    return 1;
}