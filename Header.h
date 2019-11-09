#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct {
    int count;
    char *code;
} Head;

Head *Global_head;

typedef struct {
    unsigned char data;
    int value;
} Token;

void getToken(int num, Token *token);