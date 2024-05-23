/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** env_prnt
*/

#include "my.h"

int put_env(char **env)
{
    if (!env)
        return 21;
    for (int i = 0; env[i]; i++)
        my_printf("%s\n", env[i]);
    return 21;
}
