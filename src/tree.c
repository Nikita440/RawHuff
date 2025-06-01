#include<stdio.h>
#include<stdlib.h>
#include"searcher.h"
#include"table.h"


HuffNode * create_leaf(unsigned char symbol){
    HuffNode * node = malloc(sizeof(HuffNode));
    node->symbol = symbol;
    node->left = NULL;
    node->right = NULL;
    return node;
}
HuffNode * create_internal(HuffNode*left,HuffNode*right){
    HuffNode * node = malloc(sizeof(HuffNode));
    node->symbol = 0;
    node->left = left;
    node->right = right;
    return node;

}
HuffNode* create_tree(struct FreqTable table[256]){
    table[0].Code = 0b00000000;
    table[0].Code_size = 2;
    table[1].Code = 0b00000010;
    table[1].Code_size = 2;
    table[2].Code = 0b00000010;
    table[2].Code_size = 3;
    table[3].Code = 0b00000110;
    table[3].Code_size = 3;
    table[4].Code = 0b00000110;
    table[4].Code_size = 4;
    table[5].Code = 0b00001110;
    table[5].Code_size = 4;
    table[6].Code = 0b00001110;
    table[6].Code_size = 5;
    table[7].Code = 0b00011110;
    table[7].Code_size = 5;
    table[8].Code = 0b00011110;
    table[8].Code_size = 6;
    table[9].Code = 0b00111110;
    table[9].Code_size = 6;
   
    

    HuffNode* leaf0 = create_leaf(table[0].Symbol);
    HuffNode* leaf1 = create_leaf(table[2].Symbol);
    HuffNode* leaf2 = create_leaf(table[4].Symbol);
    HuffNode* leaf3 = create_leaf(table[6].Symbol);
    HuffNode* leaf4 = create_leaf(table[8].Symbol);
    HuffNode* leaf5 = create_leaf(table[1].Symbol);
    HuffNode* leaf6 = create_leaf(table[3].Symbol);
    HuffNode* leaf7 = create_leaf(table[5].Symbol);
    HuffNode* leaf8 = create_leaf(table[7].Symbol);
    HuffNode* leaf9 = create_leaf(table[9].Symbol);
    HuffNode* int12 = create_internal(NULL,NULL);
    HuffNode* int11 = create_internal(leaf9,int12);
    HuffNode* int10 = create_internal(leaf8,int11);
    HuffNode* int9 = create_internal(leaf7,int10); 
    HuffNode* int7 = create_internal(NULL,NULL); 
    HuffNode* int6 = create_internal(leaf4,int7); 
    HuffNode* int5 = create_internal(leaf3,int6); 
    HuffNode* int8 = create_internal(leaf6,int9); 
    HuffNode* int4 = create_internal(leaf2,int5); 
    HuffNode* int3 = create_internal(leaf1,int4); 
    
    
    HuffNode* int1 = create_internal(leaf0,int3);
    HuffNode* int2 = create_internal(leaf5,int8);
    HuffNode* int0 = create_internal(int1,int2);
    
    return int0;

}
