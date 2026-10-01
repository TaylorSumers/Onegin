#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "io.h"
int readFile(const char* path, char* buff, size_t rowsAmt, size_t rowLen){
    assert(path);
    assert(buff);

    FILE* file = fopen(path, "rb");
    if (file == NULL){
        perror(path);
        return -1;
    }
    fread(buff, sizeof(char), rowsAmt * rowLen, file);
    fclose(file);

    return 0;
}

int saveFile(const char* path, char** index, size_t rowsAmt){
    assert(path);
    assert(index);

    FILE* file = fopen(path, "w");
    if (file == NULL){
        perror(path);
        return -1;
    }
    for (size_t i = 0; i < rowsAmt; i++){
        fputs(index[i], file);
    }
    fclose(file);
    
    return 0;
}