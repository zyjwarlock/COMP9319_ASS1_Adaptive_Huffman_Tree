#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanTree.h"


int header[256];

typedef struct {
    unsigned char *code;
    int len;
    int count;
    unsigned char last;
} _enCode;

typedef struct {
    unsigned char *code;
    int len;
    int flag;
    unsigned char last;
    Node *node;
} _deCode;

int readFile(char *_path);

int readHeader(char *path);

int writeBinary(char *output, char*src);

int writeFile(char *output, char *src, int num);