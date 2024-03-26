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
    int cells = 0;

    for (; env[cells] != NULL; cells++)
    out = malloc(sizeof(char *) * (cells + 1));
    for (int i = 0; i < cells; i++)
        out[i] = my_strdup(env[i]);
    out[cells - 1] = NULL;
    return out;
}
