
huffman: huffman.c Header.o BTtree.o Fileload.o HuffmanTree.o MinHeap.o Coding.o
	gcc huffman.c Header.o BTtree.o Fileload.o HuffmanTree.o MinHeap.o Coding.o -o huffman

Coding.o: Coding.c
	gcc -c Coding.c

MinHeap.o: MinHeap.c
	gcc -c MinHeap.c

HuffmanTree.o: HuffmanTree.c
	gcc -c HuffmanTree.c

Fileload.o: Fileload.c
	gcc -c Fileload.c

BTtree.o: BTtree.c
	gcc -c BTtree.c

Header.o: Header.c
	gcc -c Header.c

clean:
	rm *.o huffman