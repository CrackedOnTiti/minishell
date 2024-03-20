/*
** EPITECH PROJECT, 2023
** my_strcmp.c
** File description:
** idk
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    int result = 0;

    while (s1[i] != '\0' && s2[j] != '\0') {
        if (s1[i] != s2[j]) {
            result = (s1[i] - s2[j]);
            return (result);
        }
        i++;
        j++;
    }
    return 0;
}
