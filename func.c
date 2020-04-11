#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "func.h"

uint32_t fileSize(FILE* fp){
    if(fp){
        fseek(fp, 0, SEEK_END);
        return(ftell(fp));
    } else {
        return(0);
    }
}

uint8_t* fileBuffer(FILE* fp, uint32_t fsize){
    uint8_t* fbuffer;
    if((fbuffer = malloc(fsize * sizeof(uint8_t)))){
        fseek(fp, 0, SEEK_SET);
        fread(fbuffer, sizeof(uint8_t), fsize, fp);
        return(fbuffer);
    } else {
        return(0);
    }
}

void dumpBuffer(uint8_t* fbuffer, uint32_t fsize){
    printf("\n  Address  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    printf("\n0x%08X ", 0);
    for(uint32_t i = 1; i < fsize + 1; i++){ // this would break at UINT32_MAX
        printf("%02"PRIX8" ", fbuffer[i-1]);
        if(i % 16 == 0){
            printf("\n0x%08"PRIX32" ", i);
        }
    }
    printf("\n");
}

void dumpBufferRange(uint8_t* fbuffer, uint32_t addr1, uint32_t addr2, uint32_t fsize){
    if(!(addr1 > fsize)){
        for(uint32_t i = addr1; i <= addr2; i++){
            printf("\n0x%08"PRIX32" %02"PRIX8, i, fbuffer[i]);
        }
        printf("\n");
    }
}

void dumpBufferToFile(uint8_t* fbuffer, char* filename, uint32_t fsize){
    FILE* fp;
    if((fp = fopen(filename, "w"))){
        fprintf(fp, "  Address  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
        fprintf(fp, "\n0x%08X ", 0);
        for(uint32_t i = 1; i < fsize + 1; i++){
            fprintf(fp, "%02"PRIX8" ", fbuffer[i-1]);
            if(i % 16 == 0){
                fprintf(fp, "\n0x%08"PRIX32" ", i);
            }
        }
    } else {
        printf("Error creating file %s\n", filename);
    }
}

void editByte(uint8_t* fbuffer, uint8_t value, uint32_t addr, uint32_t fsize){
    if(!(addr>fsize)){
        fbuffer[addr] = value;
    }
}

void writeBufferToFile(uint8_t* fbuffer, char* filename, uint32_t fsize){
    FILE* fp;
    if((fp = fopen(filename, "wb"))){
        if(fwrite(fbuffer, sizeof(uint8_t), fsize, fp)){
            printf("%"PRIu32" bytes written to file %s\n", fsize, filename);
        } else {
            printf("Error writing to file %s\n", filename);
        }
    } else {
        printf("Error creating file %s\n", filename);
    }
}

void writeByteToRange(uint8_t* fbuffer, uint32_t addr1, uint32_t addr2, uint32_t fsize, uint8_t value){
    if(!(addr2 > fsize)){
        for(uint32_t i = addr1; i <= addr2; i++){
            fbuffer[i] = value;
        }
    }
}

void printHelp(){
    printf("\n-b: Dump buffer contents\n");
    printf("-d: Dump buffer at address range\n");
    printf("-e: Edit byte at desired address\n");
    printf("-f: Dump buffer contents to text file\n");
    printf("-r: Write byte to address range\n");
    printf("-s: Save file\n");
    printf("-w: Write buffer to file\n");
    printf("-x: Exit\n\n");
}

void processCommand(char command, uint32_t addr1, uint32_t addr2, uint8_t value, uint8_t* fbuffer, uint32_t fsize, char* argv){
    char filename[255];
    switch(command){
        case '?':
            printHelp();
            break;
        case 'b':
            dumpBuffer(fbuffer, fsize);
            break;
        case 'd':
            dumpBufferRange(fbuffer, addr1, addr2, fsize);
            break;
        case 'e':
            // addr2 is the value here
            editByte(fbuffer, (uint8_t)addr2, addr1, fsize);
            break;
        case 'f':
            printf("Enter file name: ");
            fgets(filename, 255, stdin);
            dumpBufferToFile(fbuffer, strtok(filename, "\n"), fsize);
            break;
        case 'r':
            writeByteToRange(fbuffer, addr1, addr2, fsize, value);
            break;
        case 's':
            writeBufferToFile(fbuffer, argv, fsize);
            break;
        case 'w':
            printf("Enter file name: ");
            fgets(filename, 255, stdin);
            writeBufferToFile(fbuffer, strtok(filename, "\n"), fsize);
            break;
        case 'x':
            printf("Exiting\n");
            break;
        default:
            printf("Unknown command\n");
            break;
    }
}

void menu(uint8_t* fbuffer, uint32_t fsize, char* argv){
    char command[25], c;
    uint8_t value = 0;
    uint32_t addr1 = 0, addr2 = 0;
    while(c != 'x'){
        printf("-");
        fgets(command, 20, stdin);
        sscanf(command, "%c %"SCNx32" %"SCNx32" %"SCNx8, &c, &addr1, &addr2, &value);
        processCommand(c, addr1, addr2, value, fbuffer, fsize, argv);
    }
}