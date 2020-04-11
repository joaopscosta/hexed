#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "func.h"

int main(int argc, char* argv[]){
    FILE* fp;
    uint32_t fsize;
    uint8_t* fbuffer;
    if(argc == 2){
        if((fp = fopen(argv[1], "rb"))){
            fsize = fileSize(fp);
            if(fsize < UINT32_MAX){
                if((fbuffer = fileBuffer(fp, fsize))){
                    fclose(fp);
                    printf("File size is %"PRIu32" bytes.\n", fsize);
                    printf("Type ? for help.\n\n");
                    menu(fbuffer, fsize, argv[1]);
                } else {
                    printf("Error allocating file buffer.\n");
                }
            } else {
                printf("\'%s\' is too big to process.\n", argv[1]);
            }
        } else {
            printf("Error opening file \'%s\'.\n", argv[1]);
        }
    } else {
        printf("Syntax: hexed \"filename\"\n");
    }
    free(fbuffer);
    return(0);
}