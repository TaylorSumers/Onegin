#include <stddef.h>
int readFile(const char* path, char* buff, size_t rowsAmt, size_t rowLen);
int saveFile(const char* path, char** index, size_t rowsAmt);
void printStrings(char* index[]);