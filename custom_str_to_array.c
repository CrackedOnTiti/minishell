/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_fucked_up_str_to_word_array
*/
#include "my.h"

int cell_counter(char const *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            count++;
    }
    return (count + 2);
}
