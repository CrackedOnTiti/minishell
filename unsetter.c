/*
** EPITECH PROJECT, 2024
** B-PSU-200-TLS-2-1-minishell2-thierry.bungaroo
** File description:
** unsetter.c
*/
#include "my.h"

static int err_hnd(int len)
{
    int is_a_tty = isatty(0);

    if (len == 1) {
        write(2, "unsetenv: Too few arguments.\n", 30);
        if (!is_a_tty)
            exit(1);
        return 84;
    }
    return 0;
}

static char **var_remove(char **env, int i)
{
    char **env_cpy = NULL;
    int env_len = 0;
    int x = 0;

    for (; env[env_len]; env_len++);
    env_cpy = malloc(sizeof(char *) * env_len);
    env_cpy[env_len - 1] = NULL;
    for (int j = 0; env[j]; j++) {
        if (i == j)
            j++;
        if (j == env_len)
            break;
        env_cpy[x] = my_strdup(env[j]);
        x++;
    }
    return env_cpy;
}

static char **is_in_env(char *arg, char **env)
{
    char *formatter = malloc(sizeof(char) * my_strlen(arg) + 2);

    formatter = my_strcpy(formatter, arg);
    formatter = my_strcat(formatter, "=\0");
    for (int i = 0; env[i] != NULL; i++)
        if (!my_strncmp(formatter, env[i], my_strlen(formatter)))
            return var_remove(env, i);
    return env;
}

char **my_notsetenv(char **input, char **env)
{
    int input_len = 0;

    for (; input[input_len] != NULL; input_len++);
    if (err_hnd(input_len))
        return env;
    for (int i = 1; i != (input_len - 1) + 1; i++)
        env = is_in_env(input[i], env);
    return env;
}
