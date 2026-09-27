#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "io.h"
void readFile(const char* path, char* buff, size_t rowsAmt, size_t rowLen){
    assert(path);
    assert(buff);

    FILE* file = fopen(path, "rb");
    fread(buff, sizeof(char), rowsAmt * rowLen, file);
    fclose(file);
}

void saveFile(const char* path, char** index, size_t rowsAmt){
    assert(path);
    assert(index);

    FILE* file = fopen(path, "w");
    for (size_t i = 0; i < rowsAmt; i++){
        fputs(index[i], file);
    }
    fclose(file);
}

void printStrings(char* index[]){
    assert(index);

    for(size_t i = 0; i < 20; i++){
        puts(index[i]);
    }
}