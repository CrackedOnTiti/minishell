/*
** EPITECH PROJECT, 2023
** built_in
** File description:
** cd_n_shit
*/
#include "my.h"

char **is_built_in(char **input, char **env, int *is_passed)
{
    if (my_strncmp(input[0], "cd", 2) == 0) {
        change_direc(input);
        *is_passed = 1;
        return env;
    }
    if (my_strncmp(input[0], "env", 3) == 0) {
        *is_passed = 1;
        put_env(env);
        return env;
    }
    if (my_strncmp(input[0], "setenv", 6) == 0) {
        env = my_setenv(input, env);
        *is_passed = 1;
        return env;
    }
    if (my_strncmp(input[0], "unsetenv", 8) == 0) {
        env = my_notsetenv(input, env);
        *is_passed = 1;
        return env;
    }
    return env;
}
