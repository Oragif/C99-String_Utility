#include "string_util.h"
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>
//Should be 32, but just in case
#define ANSI_CASE_DIF 'a' - 'A'
#define NOTFOUND -1

//Prototypes for utility functions
_Bool char_is_upper(char _char);
_Bool char_is_lower(char _char);
void str_offset_index(char **string, int index, int offset);

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
 *       Contains char or string functions         *
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
 * @param to_find char*, string to find
 * @param case_sensitive _Bool, whether to ignore case
 * @return index of first letter if found, otherwise -1
 */
int str_contains_str(char* string, char* to_find, _Bool case_sensitive) {
    if (!case_sensitive) {
        str_to_lower(&string);
        str_to_lower(&to_find);
    }
    //Find the first char in string
    int first_index = str_contains_char(string, to_find[0]);
    if (first_index != NOTFOUND) {
        int count = 1;
        //Keep checking until either full string found, out of bounds on either strings or character didn't match
        for (int j = 1; to_find[j] != '\0' && string[first_index + j] != '\0' && to_find[j] == string[first_index + j]; ++j)
            ++count;
        //Check if a string match was found, if so return index of first char
        if (count == strlen(to_find)) return first_index;
    }
    return NOTFOUND;
}

/* =============================================== *
 *        Replace string and char functions        *
 * =============================================== */

/**
 * @brief Replaces all instances of a string\n
 * If size changes the string will be reallocated to match\n
 * !! Remember to set deallocate if the inputted string is in heap !!
 * @param string char*, string to replace in
 * @param to_find char*, string to replace
 * @param to_replace char*, string to replace with
 * @param case_sensitive _Bool, whether to ignore case
 * @param deallocate _Bool, whether to deallocate the inputted string if size changes
 * @return
 */
char* str_replace_str(char *string, char* to_find, char* to_replace, _Bool case_sensitive, _Bool deallocate) {
    char* ret_str;
    _Bool free_ret_str = false;
    int to_replace_len = (int) strlen(to_replace),
        to_find_len    = (int) strlen(to_find);

    //If replacing word is bigger, then what it's replacing more memory is needed to do replacement
    if (to_find_len < to_replace_len) {
        //Calculate the maximum size, meaning if every word is replaced
        size_t max_str_size = (strlen(string)/ to_find_len) * to_replace_len + 1;
        //Allocate and copy original string
        ret_str = (char*) malloc( max_str_size * sizeof(char));
        strcpy(ret_str, string);
        free_ret_str = true;
    } else {
        //Otherwise duplicate the string to avoid memory errors
        ret_str = strdup(string);
    }

    int index = 0,
        string_offset = 0,
        index_offset  = to_replace_len - to_find_len + 1;
    _Bool changed = false;
    //Loop as long as words is being found
    do {
        //Try to find word
        // !!!!!! Index fucked, plz fix !!!!!!
        char* next =  &ret_str[index + string_offset];
        index = str_contains_str(next, to_find, case_sensitive);
        printf("%d + %d = %d\n", index, string_offset, index + string_offset);
        if (index != NOTFOUND) {
            //Offset string so new word fits
            str_offset_index(&ret_str, index, index_offset);
            //Replace character with the replacing word
            for (int i = 0; i < to_replace_len; ++i)
                ret_str[index + i] = to_replace[i];
            //Count the total offset added
            string_offset += index_offset;
            changed = true;
        }
    } while (index != NOTFOUND);

    //If anything has changed update string
    if (changed) {
        //Create a stop to string encase more memory has been allocated
        int new_size = string_offset + (int) strlen(string);
        ret_str[new_size] = '\0';

        //If the two words are equal update the string and return
        if (to_replace_len == to_find_len) {
            strcpy(string, ret_str);
            return string;
        } else {
            //Otherwise create new allocation with correct size and set it to the replaced string
            char* retPtr = (char*) malloc(new_size * sizeof(char ));
            strcpy(retPtr, ret_str);
            //Free if allocated
            if (free_ret_str) free(ret_str);
            if (deallocate)   free(string);
            return retPtr;
        }
    }

    if (free_ret_str) free(ret_str);

    return string;
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

/**
 * @brief Moves part of a string by an offset\n
 * !! Make sure enough space is allocated for new string !!
 * @param string char**, string to alter
 * @param index int, index of split, everything after will be moved by the offset
 * @param offset int, how much offset after split
 */
void str_offset_index(char **string, int index, int offset) {
    if (offset == 0) return;

    char* ret_str = strdup(*string);
    char* offset_str = strdup(&ret_str[index]);

    ret_str[index + offset] = '\0';
    for (int i = index; i < (index + offset); ++i) {
        ret_str[i] = ' ';
    }
    strcat(ret_str, offset_str);
    *string = ret_str;
}