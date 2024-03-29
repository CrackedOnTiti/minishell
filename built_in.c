/*
** EPITECH PROJECT, 2023
** built_in
** File description:
** cd_n_shit
*/
#include "my.h"

int is_built_in(char **input, char **env)
{
    if (my_strncmp(input[0], "cd", 2) == 0) {
        if (change_direc(input) == 21)
            return 69;
        return 1;
    }
    if (my_strncmp(input[0], "env", 3) == 0) {
        if (put_env(env) == 21)
            return 69;
    }
    if (my_strncmp(input[0], "setenv", 6) == 0) {
        return 1;
    }
    if (my_strncmp(input[0], "unsetenv", 8) == 0) {
        return 1;
    }
    return 0;
}
