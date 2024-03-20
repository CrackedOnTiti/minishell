/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** jsp nn plus je vais me tirer une balle
*/
#include "my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i = i + 1;
    }
    return (i);
}
