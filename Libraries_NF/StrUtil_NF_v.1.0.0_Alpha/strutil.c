// Example for testing String Utility Library (StrUtil_NF)
// Author: Nico Fontani
// Date: 8 Nov 2024


#include "strutil.h"

/* Counts the occurrences of a character in a string */
int str_count(const char* str, char ch) {
    int count = 0;
    while (*str) {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

/* Replaces all occurrences of a character in a string with a new character */
void str_replace(char* str, char old_ch, char new_ch) {
    while (*str) {
        if (*str == old_ch) {
            *str = new_ch;
        }
        str++;
    }
}

/* Concatenates two strings */
void str_concat(char* dest, const char* src) {
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  /* Null-terminate the destination string */
}

/* Finds a substring within a string */
char* str_find(const char* str, const char* sub_str) {
    if (*sub_str == '\0') return (char*)str;  /* Empty substring is always found */
    while (*str) {
        const char* s1 = str;
        const char* s2 = sub_str;
        while (*s1 && *s2 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        if (*s2 == '\0') {
            return (char*)str;  /* Found substring */
        }
        str++;
    }
    return NULL;  /* Substring not found */
}
