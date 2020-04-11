#ifndef FUNC_H
#define FUNC_H
uint32_t fileSize(FILE*);
uint8_t* fileBuffer(FILE*, uint32_t);
void dumpBuffer(uint8_t*, uint32_t);
void dumpBufferRange(uint8_t*, uint32_t, uint32_t, uint32_t);
void dumpBufferToFile(uint8_t*, char*, uint32_t);
void editByte(uint8_t*, uint8_t, uint32_t, uint32_t);
void writeBufferTofile(uint8_t*, char*, uint32_t);
void writeBufferToFile(uint8_t*, char*, uint32_t);
void writeByteToRange(uint8_t*, uint32_t, uint32_t, uint32_t, uint8_t);
void printHelp();
void menu(uint8_t*, uint32_t, char*);
void processCommand(char, uint32_t, uint32_t, uint8_t, uint8_t*, uint32_t, char*);
#endif