#include <stdio.h>
#include "Coding.h"

int main( int argc, char *argv[] ){
    //encode("test.txt", "output.huffman");
    //decode("output.huffman", "a.txt");

    if(strcmp(argv[1], "-e")==0){
        encode(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "-d")==0){
        decode(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "-s")==0){
        
    }
    else{
        return 0;
    }
    return 1;
}