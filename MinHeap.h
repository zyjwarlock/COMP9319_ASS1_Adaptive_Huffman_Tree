#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "Fileload.h"


typedef struct {

    int Max_Size;
    int Current_Size;
    Huffman *que;

} Heap;

Heap *MinHeap(int Max_Size);

int insertQue(Heap *heap, Huffman tree);

Huffman removeMin(Heap *heap);

int IsEmpty(Heap *heap);

int getLen(Heap *heap);

