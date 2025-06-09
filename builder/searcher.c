#include<stdio.h>
#include<stdlib.h>
#include"searcher.h"
#include"table.h"
#include<stdint.h>
char * readFile(char * name,size_t * out_size){
    FILE * file = fopen(name,"rb");
    if(!file){
        perror("File not found");
    }
    fseek(file,0,SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* buffer = calloc(1,size);

    size_t read_size = fread(buffer,1,size,file);
    if(size != read_size){
        perror("The size off the file didnt fir in the buffer");
    }
    
    *out_size = size;

    fclose(file);
    return buffer;
}

void scanner(char * buffer,int freq[256],size_t size){

    for(int i = 0; i < size;i++){
        unsigned  char letter = buffer[i];
        freq[letter]++;
       
    }
    

}
void createFreqtables(struct FreqTable table[256], int freq[256]) {
    int index = 0;
    int maxFreq = 0;

    // Find the maximum frequency
    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }
    

    // Fill the table from highest frequency to lowest
    for (int count = maxFreq; count > 0; count--) {
        for (int i = 0; i < 256; i++) {
            if (freq[i] == count) {
                table[index].Symbol = (char)i;
                table[255].Symbol = 'l';
                freq[i] = -1;  // Mark as used
                index++;
            }
        }
    }
}