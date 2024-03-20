/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** task02 Day04
*/
#include "my.h"

void my_putchar3(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar3(str[i]);
        i++;
    }
    return (i);
}
