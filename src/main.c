#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "str_compare.h"
#include "quick_sort.h"
#include "io.h"

const size_t ROWS_AMT = 5314;
const size_t ROW_LEN = 50;
const char* CONTENT_PATH = "content.txt";

void addTerminator(char* s){
    assert(s);

    size_t len = strlen(s);
    s[len] = '\n';
    s[len+1] = '\0';
}

char** getIndexArray(char* content, size_t rowsAmt){
    assert(content);

    char** index = (char**)calloc(rowsAmt, sizeof(char*));
    assert(index);

    index[0] = content;
    char* next = strchr(content, '\n');
    for (size_t i = 1; next != NULL && i < rowsAmt; i++){
        *next = '\0';
        index[i] = next + 1;
        next = strchr(next + 1, '\n');
    }

    addTerminator(index[rowsAmt - 1]);
    return index;
}

char** getIndexCpy(char** index, size_t rowsAmt){
    char** indexCpy = (char**)calloc(rowsAmt, sizeof(char*));
    assert(indexCpy);

    for (size_t i = 0; i < rowsAmt; i++){
        indexCpy[i] = index[i];
    }
    return indexCpy;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        puts("invalid arguments");
        return 1;
    }
    const char* outputDirectFilename = argv[1];
    const char* outputReverseFilename = argv[2];
    const char* outputOriginalFilename = argv[3];

    char* content = (char*)calloc(ROWS_AMT * ROW_LEN, sizeof(char));
    assert(content);

    readFile(CONTENT_PATH, content, ROWS_AMT, ROW_LEN);
    char** index = getIndexArray(content, ROWS_AMT);
    char** indexCpy = getIndexCpy(index, ROWS_AMT);

    // Direct sort
    qsort(index, ROWS_AMT, sizeof(char*), &directCmp);
    saveFile(outputDirectFilename, index, ROWS_AMT); 
    
    // Reverse sort
    myQsort(index, ROWS_AMT, &reverseCmp);
    saveFile(outputReverseFilename, index, ROWS_AMT);

    // Original
    saveFile(outputOriginalFilename, indexCpy, ROWS_AMT);
    
    free(index);
    free(indexCpy);
    free(content);
}
