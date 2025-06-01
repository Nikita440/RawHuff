#include<stdio.h>
#include<stdlib.h>
#include"searcher.h"
#include"table.h"

uint8_t* Build(size_t size, struct FreqTable table[256], char* buff) {
    // Reset code sizes for entries past index 9
    for (int h = 10; h < 256; h++) {
        table[h].Code_size = 0;
    }

    // Build a lookup table: symbol -> first table index with code assigned
    int symbol_to_index[256];
    for (int i = 0; i < 256; i++) {
        symbol_to_index[i] = -1;  // -1 means no coded entry found yet
    }
    for (int i = 0; i < 256; i++) {
        unsigned char sym = (unsigned char)table[i].Symbol;
        if (table[i].Code_size != 0 && symbol_to_index[sym] == -1) {
            symbol_to_index[sym] = i;
        }
    }

    size_t index = 0;        // byte index in arr
    size_t buff_point = 0;   // bit position in current byte (0-7)
    uint8_t* arr = calloc(size * 2, sizeof(uint8_t));  // output buffer

    for (size_t j = 0; j < size; j++) {
        unsigned char let = (unsigned char)buff[j];
        int i = symbol_to_index[let];

        if (i == -1) {
            // No coded entry found, fallback to first entry with Code_size == 0
            for (i = 0; i < 256; i++) {
                if (table[i].Symbol == let && table[i].Code_size == 0) {
                    break;
                }
            }
            if (i == 256) {
                // Symbol not found in table at all, skip or handle error
                continue;
            }
        }

        uint8_t code_size = table[i].Code_size;
        uint16_t code = table[i].Code;

        if (code_size != 0) {
            // Encode the code bits into arr
            if (buff_point == 0 && code_size <= 8) {
                int shift = 8 - code_size;
                arr[index] = code << shift;
                buff_point += code_size;
            } else if (buff_point + code_size <= 8) {
                int shift = 8 - code_size - buff_point;
                arr[index] |= code << shift;
                buff_point += code_size;
            } else {
                int left_bits = 8 - buff_point;
                int overflow_bits = code_size - left_bits;
                arr[index] |= code >> overflow_bits;
                index++;
                arr[index] = code << (8 - overflow_bits);
                buff_point = overflow_bits;
                continue;
            }

            if (buff_point == 8) {
                index++;
                buff_point = 0;
            }
        } else {
            // Fallback mode: encode 2-bit prefix (0b10) + raw 8-bit symbol

            // Encode 2-bit prefix
            if (buff_point + 2 <= 8) {
                int shift = 8 - 2 - buff_point;
                arr[index] |= 0b10 << shift;
                buff_point += 2;
                if (buff_point == 8) {
                    index++;
                    buff_point = 0;
                }
            } else {
                int left = 8 - buff_point;
                int shift = 2 - left;
                arr[index] |= 0b10 >> shift;
                index++;
                arr[index] = 0b10 << (8 - shift);
                buff_point = shift;
            }

            // Encode the raw 8-bit symbol
            if (buff_point + 8 <= 8) {
                int shift = 8 - 8 - buff_point;  // shift will be 0
                arr[index] |= table[i].Symbol << shift;
                buff_point += 8;
                if (buff_point == 8) {
                    index++;
                    buff_point = 0;
                }
            } else {
                int left = 8 - buff_point;
                int shift = 8 - left;
                arr[index] |= table[i].Symbol >> shift;
                index++;
                arr[index] = table[i].Symbol << (8 - shift);
                buff_point = shift;
            }
        }
    }

    // Flush remaining bits if any
    if (buff_point > 0) {
        index++;
    }

    return arr;
}
char * Build_Serialized_tree(struct FreqTable table[256]){

    int index = 0;
    char * tree = calloc(10,sizeof(char));

    tree[0] = table[0].Symbol;//from here---
    tree[1] = table[2].Symbol;
    tree[2] = table[4].Symbol;
    tree[3] = table[6].Symbol;
    tree[4] = table[8].Symbol;//to here--- It will be the left side symbols,since we know that there
    //are 5 of them when creating a tree we can place starting from first value on the left and same with a differnt branch
    tree[5] = table[1].Symbol; 
   
   
    tree[6] = table[3].Symbol;
    tree[7] = table[5].Symbol;
    tree[8] = table[7].Symbol;
    tree[9] = table[9].Symbol;

   return tree;



}

