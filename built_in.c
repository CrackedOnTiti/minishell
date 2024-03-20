/*
** EPITECH PROJECT, 2023
** built_in
** File description:
** cd_n_shit
*/
#include "my.h"

int is_built_in(char **input)
{
    if (my_strncmp(input[0], "cd", 2) == 0) {
        if (change_direc(input) == 21)
            return 69;
        return 1;
    }
    return 0;
}
