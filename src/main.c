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

void freeAll(char** index, char** indexCpy, char* content){
    free(index);
    free(indexCpy);
    free(content);
}

int main(int argc, char *argv[]){
    const char* outputDirectFilename = argc > 1 ? argv[1] : "output_direct.txt";
    const char* outputReverseFilename = argc > 2 ? argv[2] : "output_reverse.txt";
    const char* outputOriginalFilename = argc > 3 ? argv[3] : "output_original.txt";

    char* content = (char*)calloc(ROWS_AMT * ROW_LEN, sizeof(char));
    assert(content);

    if(readFile(CONTENT_PATH, content, ROWS_AMT, ROW_LEN) == -1){
        free(content);
        return -1;
    }

    char** index = getIndexArray(content, ROWS_AMT);
    char** indexCpy = getIndexCpy(index, ROWS_AMT);

    // Direct sort
    qsort(index, ROWS_AMT, sizeof(char*), &directCmp);
    if(saveFile(outputDirectFilename, index, ROWS_AMT) == -1){
        freeAll(index, indexCpy, content);
        return -1;
    }
    
    // Reverse sort
    myQsort(index, ROWS_AMT, &reverseCmp);
    if(saveFile(outputReverseFilename, index, ROWS_AMT) == -1){
        freeAll(index, indexCpy, content);
        return -1;
    }

    // Original
    if(saveFile(outputOriginalFilename, indexCpy, ROWS_AMT) == -1){
        freeAll(index, indexCpy, content);
        return -1;
    }
    
    freeAll(index, indexCpy, content);
}
