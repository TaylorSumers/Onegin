#include <stddef.h>
void readFile(const char* path, char* buff, size_t rowsAmt, size_t rowLen);
void saveFile(const char* path, char** index, size_t rowsAmt);
void printStrings(char* index[]);