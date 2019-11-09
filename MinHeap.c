#include <stdio.h>
#include <malloc.h>
#include "MinHeap.h"


Heap *MinHeap(int Max_Size){
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->Max_Size = Max_Size;
    heap->Current_Size = 0;
    heap->que = (Huffman *)malloc(sizeof(Huffman)*Max_Size);
    return heap;
}

void filterUp(int start, Heap *heap){
    int j=start;
    //printf("%d    ", j);
    int i=j>0 ? (j-1)/2 : 0;
    Huffman tmp = heap->que[j];
    //printf("tmp:%c\n", tmp.tree->root->ch);
    while(j>0){
        if(heap->que[i].value<tmp.value) break;
        else{
            //printf("tmp:%c === j:%c === i:%c\n" 
             //   , tmp.tree->root->ch, heap->que[j].tree->root->ch, heap->que[i].tree->root->ch);
            heap->que[j] = heap->que[i];
            //printf("======== j:%c ===========\n",heap->que[j].tree->root->ch);
            j=i;
            i=(i-1)/2;
        }
    }
    heap->que[j] = tmp;
    //printf("%d    %c\n", start,  heap->que[start].tree->root->ch);
}

void filterDown(int start, int end, Heap *heap){
    int i=start;
    int j=2*i+1;

    Huffman tmp = heap->que[i];

    while(j<=end){
        if( (j<end) && (heap->que[j].value > heap->que[j+1].value)) j++;
        if( tmp.value <= heap->que[j].value) break;
        else{
            heap->que[i] = heap->que[j];
            i=j;
            j=2*j+1;
        }
    } 
    heap->que[i] = tmp;
    
}

int insertQue(Heap *heap, Huffman tree){

    if(heap->Current_Size == heap->Max_Size){
        return 0;
    }
    heap->que[heap->Current_Size] = tree;
    filterUp(heap->Current_Size, heap);

    heap->Current_Size++;
    return 1;
}

Huffman removeMin(Heap *heap){

    //printf("%d     ", heap->que[0].value);
    Huffman tree = heap->que[0];
    heap->que[0] = heap->que[heap->Current_Size-1];
    heap->Current_Size--;
    filterDown(0, heap->Current_Size-1, heap);

    return tree;
}

Huffman getMin(Heap *heap){
    return heap->que[0];
}

int IsEmpty(Heap *heap){
    return (heap->Current_Size == 0);
}

int getLen(Heap *heap){
    return heap->Current_Size;
}





