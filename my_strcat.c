/*
** EPITECH PROJECT, 2023
** my_strcat.c
** File description:
** task02
*/

#include "my.h"

char *my_strcat(char *dest, const char *src)
{
    int i = my_strlen(dest);

    for (int j = 0; src[j] != '\0'; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
