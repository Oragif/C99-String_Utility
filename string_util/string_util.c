#include "string_util.h"
#include <string.h>
#include <stdbool.h>
//Should be 32, but just in case
#define ANSI_CASE_DIF 'a' - 'A'
#define NOTFOUND -1

//Prototypes for utility functions
_Bool char_is_upper(char _char);
_Bool char_is_lower(char _char);

/* =============================================== *
 *         Lower- & uppercase conversion           *
 * =============================================== */

/**
 * @brief Converts char* pointer to lowercase
 * @param string char* ptr, string to convert
 */
void str_to_lower(char **string) {
    //Duplicate string to avoid memory errors
    char* str_dup = strdup(*string);
    //Run through string until end character is found
    for (size_t i = 0; str_dup[i] != '\0'; ++i)
        //Check if it's uppercase and replace it with lowercase if it is
        if (char_is_upper(str_dup[i]))
            str_dup[i] += ANSI_CASE_DIF;
    //Set inputted string to lowercase version
    *string = str_dup;
}

/**
 * @brief Converts char* pointer to uppercase
 * @param string char* ptr, string to convert
 */
void str_to_upper(char **string) {
    //Duplicate string to avoid memory errors
    char* str_dup = strdup(*string);
    //Run through string until end character is found
    for (size_t i = 0; str_dup[i] != '\0'; ++i)
        //Check if it's lowercase and replace it with uppercase if it is
        if (char_is_lower(str_dup[i]))
            str_dup[i] -= ANSI_CASE_DIF;
    //Set inputted string to uppercase version
    *string = str_dup;
}

/* =============================================== *
 *         Lower- & uppercase conversion           *
 * =============================================== */

/**
 * Finds first instance of char
 * @param string char*, string to search
 * @param c char, char to find
 * @return int, index if found, otherwise -1
 */
int str_contains_char(const char* string, char c) {
    //Run through string until end character is found
    for (int i = 0; string[i] != '\0'; ++i)
        //Check if char is found
        if (string[i] == c)
            return i;
    return NOTFOUND;
}

/**
 * Looks for a string in a string
 * @param string char*, string to search
 * @param str_to_find char*, string to find
 * @param case_sensitive _Bool, whether to ignore case
 * @return index of first letter if found, otherwise -1
 */
int str_contains_str(char* string, char* str_to_find, _Bool case_sensitive) {
    if (!case_sensitive) {
        str_to_lower(&string);
        str_to_lower(&str_to_find);
    }
    //Find the first char in string
    int first_index = str_contains_char(string, str_to_find[0]);
    if (first_index != NOTFOUND) {
        int count = 1;
        //Keep checking until either full string found, out of bounds on either strings or character didn't match
        for (int j = 1; str_to_find[j] != '\0' && string[first_index + j] != '\0' && str_to_find[j] == string[first_index + j]; ++j)
            ++count;
        //Check if a string match was found, if so return index of first char
        if (count == strlen(str_to_find)) return first_index;
    }
    return NOTFOUND;
}

/* =============================================== *
 *       Declaration for utility functions         *
 * =============================================== */

/**
 * @brief check if char is within A-Z
 * @param _char char, to check
 * @return _Bool
 */
_Bool char_is_upper(char _char) {
    if (_char >= 'A' && _char <= 'Z')
        return true;
    return false;
}

/**
 * @brief check if char is within a-z
 * @param _char char, to check
 * @return _Bool
 */
_Bool char_is_lower(char _char) {
    if (_char >= 'a' && _char <= 'z')
        return true;
    return false;
}