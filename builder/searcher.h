#include"table.h"
#ifndef SEARCHER_H
#define SEARCHER_H

char * readFile(char * name,size_t * out_size);

void scanner(char * buffer,int freq[],size_t size);

void createFreqtables(struct FreqTable table[256],int freq[]);

uint8_t* Build(size_t size,struct FreqTable table[256],char * buff);

char * Build_Serialized_tree(struct FreqTable table[256]);

#endif    