#include "Header.h"


void getToken(int num, Token *token){
    int j = 0;
    int i =0;
    for(i=0; i<256; i++){
        if(Global_head[i].count > 0){
            token[j].data = (unsigned char)i;
            token[j].value = Global_head[i].count;  
            j++;
        }
    }
}