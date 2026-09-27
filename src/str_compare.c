#include <assert.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#include "str_compare.h"

static char nextLetter(const char* s, size_t* pos, bool reverse){
    while (reverse ? *pos > 0 : s[*pos] != '\0') {
        size_t index;

        if (reverse)
            index = --(*pos); // start on s[len] == \0
        else
            index = (*pos)++; // start on s[0]

        if (isalpha(s[index]))
            return tolower(s[index]);
    }

    return 0;
}


static int cmp(const char* s1, const char* s2, bool reverse){
    size_t i = reverse ? strlen(s1): 0;
    size_t j = reverse ? strlen(s2): 0;

    while(true){
        char c1 = nextLetter(s1, &i, reverse);
        char c2 = nextLetter(s2, &j, reverse);

        if (c1 != c2){
            return (c1 > c2) - (c1 < c2);
        }
        if (c1 == '\0'){
            return 0;
        }
    }
}

int directCmp(const void* lhs, const void* rhs){
    assert(lhs);
    assert(rhs);

    const char* s1 = *(char* const*)lhs;
    const char* s2 = *(char* const*)rhs;

    return cmp(s1, s2, false);
}

int reverseCmp(const void* lhs, const void* rhs){
    assert(lhs);
    assert(rhs);
    
    const char* s1 = *(char* const*)lhs;
    const char* s2 = *(char* const*)rhs;

    return cmp(s1, s2, true);
}