#include"../src/table.h"


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

HuffNode * deserialize_tree(char * tree){

    HuffNode* leaf0 = create_leaf(tree[0]);
    HuffNode* leaf1 = create_leaf(tree[1]);
    HuffNode* leaf2 = create_leaf(tree[2]);
    HuffNode* leaf3 = create_leaf(tree[3]);
    HuffNode* leaf4 = create_leaf(tree[4]);
    HuffNode* leaf5 = create_leaf(tree[5]);
    HuffNode* leaf6 = create_leaf(tree[6]);
    HuffNode* leaf7 = create_leaf(tree[7]);
    HuffNode* leaf8 = create_leaf(tree[8]);
    HuffNode* leaf9 = create_leaf(tree[9]);
    HuffNode* int10 = create_internal(leaf9,NULL);
    HuffNode* int9 = create_internal(leaf8,int10);
    HuffNode* int8 = create_internal(leaf7,int9);
    HuffNode* int7 = create_internal(leaf6,int8);
    HuffNode* int6 = create_internal(leaf4,NULL);
    HuffNode* int5 = create_internal(leaf3,int6);
    HuffNode* int4 = create_internal(leaf2,int5);
    HuffNode* int3 = create_internal(leaf1,int4);

    HuffNode* int1 = create_internal(leaf0,int3);
    HuffNode* int2 = create_internal(leaf5,int7);
    HuffNode* int0 = create_internal(int1,int2);

    return int0;

}