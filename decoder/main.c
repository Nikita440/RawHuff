#include<stdio.h>
#include<stdlib.h>
#include"../builder/table.h"
#include<unistd.h>
#include<stdint.h>

int main(int argc,char* argv[]){

    FILE* handle = fopen(argv[1],"rb");

   
 
    
    uint32_t magic;
    uint8_t namelen;
    size_t start_size;
    char* tree = malloc(10);
    int arr_size;
    char sirtree_size;
    char* filename = malloc(64);
    fread(&magic,4,1,handle); 
    
    if(magic == 0x48554646){
        
    }else{
        printf("Wrong type of the file,cant decode.\n");
        exit(1);
    }
    fread(&namelen,1,1,handle);
    fread(filename,(size_t)namelen,1,handle);
    fread(&start_size,sizeof(size_t),1,handle);
    fread(&arr_size,sizeof(int),1,handle);
    uint8_t * bit_arr = malloc(arr_size);
    fread(&sirtree_size,1,1,handle);
    fread(tree,10,1,handle);
    fread(bit_arr,arr_size,1,handle); 
    HuffNode* root = deserialize_tree(tree);
    printf("%c",root->right->left->symbol);
    printf("%d",bit_arr[31]);  
   
    printf("%s ", tree);
    char *resbuff = decode_bits(root,bit_arr,start_size,arr_size);
    FILE * final_file = fopen(filename,"wb");
    

    fwrite(resbuff,start_size,1,final_file);
    printf("Decoded buffer: ");
for (size_t i = 0; i < start_size; i++) {
    printf("%02x ", (unsigned char)resbuff[i]);
}
printf("\n");

printf("As string: %s\n", resbuff);
printf("%zu",start_size);
    
pid_t pid;
pid = fork();

if(pid == 0){
    char * args[] = {"/bin/rm", "COMPRESSED.HUFF",NULL};
    execve("/bin/rm",args,NULL);
    exit(1);
}


}