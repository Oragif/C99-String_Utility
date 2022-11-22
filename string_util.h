#ifndef STRING_UTIL_STRING_UTIL_H
#define STRING_UTIL_STRING_UTIL_H
#include <string.h>
void str_to_lower(char **string);
void str_to_upper(char **string);
int str_contains_str(char* string, char* to_find, _Bool case_sensitive);
int str_contains_char(const char* string, char c);
char* str_replace_str(char *string, char* to_find, char* to_replace, _Bool case_sensitive, _Bool deallocate);
#endif //STRING_UTIL_STRING_UTIL_H
