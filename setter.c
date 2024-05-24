/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** setenv
*/
#include "my.h"

static char **cases(char **env, int count, char **input, int len)
{
    if (len == 2 && env) {
        env[count] = malloc(sizeof(char) * (my_strlen(input[1]) + 3));
        env[count] = my_strcpy(env[count], input[1]);
        env[count] = my_strcat(env[count], "=");
        env[count][my_strlen(input[1]) + 2] = '\0';
    }
    if (len == 3 && env) {
        env[count] = malloc(sizeof(char) *
        (my_strlen(input[1]) + my_strlen(input[2]) + 2));
        env[count] = my_strcpy(env[count], input[1]);
        env[count] = my_strcat(env[count], "=");
        env[count] = my_strcat(env[count], input[2]);
        env[count][my_strlen(input[1]) + 2 + my_strlen(input[2])] = '\0';
    }
    return env;
}

static void magik_func(int *error, char **input, int len)
{
    if (len > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        *error = 1;
    }
    if (((input[1][0] > 0 && input[1][0] < 48) || (input[1][0] > 57
        && input[1][0] < 65) || (input[1][0] > 90 && input[1][0] < 97)
        || input[1][0] > 122) && input[1][0] != '_') {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        *error = 1;
        return;
    }
    for (int i = 0; input[1][i] != '\0'; i++) {
        if (((input[1][i] > 0 && input[1][i] < 48) || (input[1][i] > 57
        && input[1][i] < 65) || (input[1][i] > 90 && input[1][i] < 97)
        || input[1][i] > 122) && input[1][i] != '_') {
            write(2, "setenv: Variable name must ", 27);
            write(2, "contain alphanumeric characters.\n", 33);
            *error = 1;
        }
    }
}

static int error_mana(int len, char **input, char **env)
{
    int is_a_tty = isatty(0);
    int error = 0;

    if (len == 1)
        return put_env(env);
    magik_func(&error, input, len);
    if (error && !is_a_tty)
        exit(1);
    else if (error)
        return 84;
    return 0;
}

static char **env_realloc(char **env, int len)
{
    char **env_cpy = NULL;

    env_cpy = malloc(sizeof(char *) * (len + 2));
    env_cpy[len + 1] = NULL;
    for (int i = 0; env && env[i]; i++)
        env_cpy[i] = env[i];
    return env_cpy;
}

char **my_setenv(char **input, char **env)
{
    int count = 0;
    int input_len = 0;

    for (; input[input_len] != NULL; input_len++);
    if (error_mana(input_len, input, env))
        return env;
    for (; env && env[count]; count++)
        if (!my_strncmp(input[1], env[count], my_strlen(input[1])) &&
        env[count][my_strlen(input[1])] == '=')
            break;
    env = env_realloc(env, count);
    env = cases(env, count, input, input_len);
    return env;
}
