#include <stdio.h>
#include <string.h>
#include "Fileload.h"

int readFile(char *_path){
    
    FILE *file = fopen(_path, "r");

    if(file == NULL){
        fclose(file);
        return 0;
    }

    unsigned char c = fgetc(file);
    while(!feof(file)){
        Global_head[c].count++;
        c = fgetc(file);   
    }
    fclose(file);
    return 1;
    
}

char *getChar(unsigned char ch){
    unsigned char le = ch;
    unsigned char standard = 1;
    char *c;
    c = (char *)malloc(sizeof(char)*8);
    int i=0;
    for (i=7; i>-1; i--){
        char flag = (standard & le);
        if(flag){
            c[i]='1';
        }
        else{
            c[i]='0';
        }
        le = le/2;
    }
    return c;
}

void encode_Huff(unsigned char ch, _enCode *code){

    int length = code->len;// length of last byte

    unsigned char last = code->last;// last code

    char *_code = Global_head[ch].code;//huffman code of current char

    int len = strlen(_code);//lenght of huffman code

    code->len = (length+len)%8;// length of the last byte


    code->count = (length+len)/8 + 1;//number of byte

    code->code = (unsigned char *)malloc(sizeof(char)*(code->count));

    code->code[0] = last;

    int i=0;
    for (i=0; i<len; i++){
        
        if(_code[i]=='1'){
            code->code[(length+i)/8] = code->code[(length+i)/8] | (1<<(7-(i+length)%8));
        }
    }
}



unsigned char decode_huff(_deCode *code){

    //printf("长度为：%d\n", code->len);
    Leaf *leaf;
    char *ch = getChar(code->code[0]);
    //printf("huffman code %s\n", ch);
    leaf = getLeaf(ch, code->node);
    //printf("leaf->ch: %c leaf->len: %d\n", leaf->ch, leaf->len);
    ch = getChar(code->code[1]);
    //printf("code 2: %s\n", ch);

    int i=0;
    for(i=0; i<leaf->len; i++){
        code->code[0] = code->code[0]*2;
        code->code[1] = code->code[1]*2;
        if(ch[i]=='1'){
            code->code[0] = (code->code[0] | 1);
        }
    }

    //printf("更新后 code 1: %s, code 2: %s\n", getChar(code->code[0]), getChar(code->code[1]));
    
    code->len = code->len - leaf->len;
    //printf("剩余长度：%d\n", code->len);
    if(leaf->flag==1){
        code->flag = 1;
    }
    return leaf->ch;
}

int readHeader(char *path){

    FILE *file = fopen(path, "rb");
    if(file == NULL){
        fclose(file);
        
        return 0;
    }
    
    int i=0;
    for(i=0; i<256; i++){
        unsigned char c = i;
        Global_head[c].count = 0;
    }
    
    for(i=0; i<256; i++){
        unsigned char c = i;
        Global_head[c].count = 0;
        fread(&Global_head[c].count, sizeof(int), 1, file);
    }

    return 1;

}

int writeFile(char *path_w, char *path_r, int num){

    FILE *file_r = NULL, *file_w = NULL;

    file_r = fopen(path_r, "rb");
    file_w= fopen(path_w, "w");
    //printf("=====%s=====\n", path_w);
    if(file_w == NULL || file_r == NULL)
    {
        fclose(file_r);
        fclose(file_w);
        printf("exit");
        return 0;
    }
    int i=0;
    for(i=0; i<1024; i++){
        fgetc(file_r);
    }
    int sum = 0;

    unsigned char *last = (unsigned char *)malloc(sizeof(char)*2);

    if(!feof(file_r)){
        last[0] = fgetc(file_r);
    }

    int len = 8;
    Node *node = huffman_tree.tree->root;
    int times = 0;
    while(sum<num){

        _deCode *code; 
        code = (_deCode *)malloc(sizeof(_deCode));
        code->code = (unsigned char *)malloc(sizeof(char)*2);
        code->code[0] = last[0];
        code->code[1] = last[1];
        code->len = len;
        code->node = node;
        code->flag = 0;


        if(code->len < 9 && !feof(file_r)){
            code->code[1] = fgetc(file_r);
            char *c = getChar(code->code[1]);
            int i=0;
            for(i=0; i<8-code->len; i++){
                if(c[i]=='1'){
                    code->code[0] = (code->code[0] | (1<<( (8 - code->len) - i - 1)));
                }
                code->code[1] = code->code[1] * 2;
            }
            code->len = code->len+8;
        }
        unsigned char letter = decode_huff(code);
        
        if(code->flag==1){
            //printf("===========正在写入 %c==========\n", letter);
            fwrite(&letter, sizeof(unsigned char), 1, file_w);
            //printf("===========写入 %c==========\n", letter);
            sum++;
        }
        len = code->len;
        last[0] = code->code[0];
        last[1] = code->code[1];
        node = code->node;
        
        
    }

    fclose(file_w);
    fclose(file_r);

    return 1;
}

int writeBinary(char *path_w, char *path_r){

    unsigned char ch;
    FILE *file_r = NULL, *file_w = NULL;
    file_r = fopen(path_r, "r");
    file_w= fopen(path_w, "wb");
    
    if(file_r == NULL || file_r == NULL)
    {
        if(file_r) fclose(file_r);
        if(file_w) fclose(file_w);
        return 0;
    }
    int i=0;
    for(i=0; i<256; i++){
        fwrite(&Global_head[i].count, sizeof(int), 1, file_w);
    }


    ch = fgetc(file_r);

    int len = 0; 
    unsigned char last;

    while(!feof(file_r)){

        _enCode *code; 
        code = (_enCode *)malloc(sizeof(_enCode));
        code -> len = len;
        code -> last = last;

        encode_Huff(ch, code);

        
        int i=0;
        for(i=1; i<code->count; i++){
            fwrite(&code->code[i-1], sizeof(char), 1, file_w);
        }

    
        if(code->len==0 && code->count>0){
            last = 0;
        }

        last= code->code[code->count-1];
        len = code->len;

        ch = fgetc(file_r);
    }
    if(len>0){
        fwrite(&last, sizeof(char), 1, file_w);
    }

    
    fclose(file_w);
    fclose(file_r);

    return 1;
}


