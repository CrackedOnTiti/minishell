/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** main_env_alloc
*/

#include "my.h"

char **env_alloc(char **env)
{
    char **out = NULL;
    int i = 0;
    int cells = 0;

    for (; env[cells] != NULL; cells++)
    out = malloc(sizeof(char *) * (cells + 2));
    for (; env[i]; i++)
        out[i] = my_strdup(env[i]);
    out[i] = NULL;
    return out;
}

char **setenv_alloc(char **env)
{
    char **out = NULL;
    int cells = 0;

    for (; env[cells] != NULL; cells++)
    out = malloc(sizeof(char *) * (cells + 2));
    for (int i = 0; i < cells; i++)
        out[i] = my_strdup(env[i]);
    out[cells] = NULL;
    out[cells + 1] = NULL;
    return out;
}
