/*
** EPITECH PROJECT, 2018
** my_strdup.c
** File description:
** description of the file
*/
#include "my.h"

int my_strlen_deux(char const *str)
{
    int n = 0;

    while (str[n] != '\0')
        n++;
    return (n);
}

char *my_strdup(char const *src)
{
    char *point;
    int index = 0;
    int length = my_strlen_deux(src);

    point = malloc(length + 1);
    while (src[index] != '\0') {
        point[index] = src[index];
        index = index + 1;
    }
    return (point);
}
