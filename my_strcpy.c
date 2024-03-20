/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** Never gunna give you up
*/
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int ctr = 0;

    while (src[ctr] != '\0') {
        dest[ctr] = src[ctr];
        ctr = ctr + 1;
    }
    dest[ctr] = '\0';
    return (dest);
}
