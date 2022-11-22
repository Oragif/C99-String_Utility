# String Utility

## Lower- & uppercase conversion 
```
Replaces string ptr with lowercase version
void str_to_lower(char **string)

Replaces string ptr with uppercase version
void str_to_upper(char **string)
```
## Find first index of char or string
Returns index of first instance
```
Find first index of string
int str_contains_str(char* string, char* str_to_find, _Bool case_sensitive);

Find first index of char
int str_contains_char(const char* string, char c);
```