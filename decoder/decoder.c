#include<stdio.h>
#include<stdlib.h>
#include"../builder/table.h"

#include<stdint.h>


char* decode_bits(HuffNode* root, uint8_t* enc_arr, size_t orig_size, int arr_size) {
    char* buff_res = malloc(orig_size + 1);
    if (!buff_res) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    int byte_index = 0;
    int bit_index = 7;
    int buff_index = 0;
    HuffNode* current = root;

    while (buff_index < orig_size && byte_index < arr_size) {
        uint8_t bit = (enc_arr[byte_index] >> bit_index) & 1;
        current = bit ? current->right : current->left;

        if (!current) {
            fprintf(stderr, "ERROR: Broken traversal\n");
            exit(1);
        }

        if (!current->left && !current->right) {
            // Reached a leaf
            if (current->symbol == 96) {
                // Special marker: read next 8 bits raw
                uint8_t symbol = 0;
                for (int i = 0; i < 8; i++) {
                    bit_index--;
                    if (bit_index < 0) {
                        bit_index = 7;
                        byte_index++;
                        if (byte_index >= arr_size) break;
                    }
                    uint8_t raw_bit = (enc_arr[byte_index] >> bit_index) & 1;
                    symbol = (symbol << 1) | raw_bit;
                }
                buff_res[buff_index++] = symbol;
            } else {
                buff_res[buff_index++] = current->symbol;
            }
            current = root; // Restart from root for next symbol
        }

        bit_index--;
        if (bit_index < 0) {
            bit_index = 7;
            byte_index++;
        }
    }

    buff_res[buff_index] = '\0'; // Safe string
    return buff_res;
}
