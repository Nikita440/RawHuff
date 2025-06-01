#include<stdio.h>
#include"searcher.h"
#include<stdlib.h>
#include"table.h"
#include<string.h>

int main(int argc,char*argv[]){
    struct FreqTable table[256];
    
    size_t size;

    const char *filename = argv[1];
    
    
    char * buff = readFile(argv[1],&size);
    printf("%zu",size);
  
   
    int freq[256] = {0};
   
    scanner(buff,freq,size); // Sets the correct values in the freq array
   
    
    createFreqtables(table,freq); //correctly orders the symbols in the FreqTable(first indexes are most frequent symbols)
     memmove(&table[2], &table[1], 8 * sizeof(struct FreqTable));

    // Insert the special raw symbol marker at index 1
    table[1].Symbol = 96;      // Your special symbol for raw 8-bit symbol
    table[1].Code = 0b10;         // Set code to zero or as needed
    table[1].Code_size = 2;    // Minimal size to mark it as special, adjust if needed


    


   
    HuffNode * root0 = create_tree(table); // creates a tree with the most frequent symbols near root
    
    uint8_t* arr = Build(size,table,buff);

   for (int i = 0; i < 30; i++) {
    printf("arr[%d] = %02X (", i, arr[i]);
    for (int b = 7; b >= 0; b--)
        printf("%d", (arr[i] >> b) & 1);
    printf(")\n");
    

    
}

int byte = 0;
    for(int i = 0;i < size;i++){
       
        if(arr[i] != 0){
            byte++;
        }
    }
    int save = size - byte;
    printf("Original size: %zu, New size: %d,Saved: %d\n",size,byte,save);
    char *sirtree = Build_Serialized_tree(table);
    for (int i = 0; i < 10; i++) {
    printf("%02X ", sirtree[i]);
    }
    printf("\n");
 
    char treesize = 10;
    
    uint32_t magic = 0x48554646;
    
    uint8_t len = strlen(filename);
    FILE * zipped = fopen("COMPRESSED.HUFF","wb");
    fwrite(&magic,sizeof(uint32_t),1,zipped); //uint32_t
    fwrite(&len,1,1,zipped);//char
    fwrite(argv[1],strlen(filename),1,zipped); // char*
    fwrite(&size,sizeof(size_t),1,zipped); //size_t
    fwrite(&byte,4,1,zipped); //int(size of byte array)
    fwrite(&treesize,1,1,zipped);//char
    fwrite(sirtree,sizeof(char),10,zipped);//uint8 *
    fwrite(arr,byte,1,zipped);//uint8 *
    
    
    

    

    
   
    


}