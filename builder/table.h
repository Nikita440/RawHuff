#include<stdio.h>
#include<stdlib.h>
#ifndef TABLE_H
#define TABLE_H

struct FreqTable{
    char Symbol;
    int Code_size;
    char Code;

};
typedef struct HuffNode {
    char symbol;
    struct HuffNode* left;
    struct HuffNode* right;
} HuffNode;
struct CurrenNode{
    HuffNode* node;
};
HuffNode * create_leaf(unsigned char symbol);
HuffNode * create_internal(HuffNode*left,HuffNode*right);
HuffNode* create_tree(struct FreqTable table[256]);
HuffNode* deserialize_tree(char *tree);
char * decode_bits(HuffNode* root,uint8_t* enc_arr,size_t orig_size,int arr_size);




#endif