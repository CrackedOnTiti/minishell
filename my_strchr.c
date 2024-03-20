/*
** EPITECH PROJECT, 2023
** custom strchr
** File description:
** custom made by yourse truly, selects a specific value in a string
*/
#include "my.h"

char *my_strchr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}
