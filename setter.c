/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** setenv
*/
#include "my.h"

static char **cases(char **env, int count, char **input, int len)
{
    if (len == 2) {
        env[count] = malloc(sizeof(char) * (my_strlen(input[1]) + 2));
        env[count] = my_strcpy(env[count], input[1]);
        env[count] = my_strcat(env[count], "=");
        env[count][my_strlen(input[1]) + 2] = '\0';
    }
    if (len == 3) {
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
        write(2, "setenv: Too many arguments.\n", 29);
        *error = 1;
    }
    if (input[1][0] > 48 && input[1][0] < 58) {
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
        *error = 1;
    }
    for (int i = 0; input[1][i] != '\0'; i++) {
        if (((input[1][i] > 0 && input[1][i] < 48) || (input[1][i] > 57
        && input[1][i] < 65) || (input[1][i] > 90 && input[1][i] < 97)
        || input[1][i] > 122) && input[1][i] != '_') {
            write(2, "setenv: Variable name must ", 28);
            write(2, "contain alphanumeric characters.\n", 34);
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

char **my_setenv(char **input, char **env)
{
    char **new_env = setenv_alloc(env);
    int count = 0;
    int is_end = 0;
    int input_len = 0;

    for (; input[input_len] != NULL; input_len++);
    if (error_mana(input_len, input, env))
        return env;
    for (; env[count]; count++)
        if (!my_strncmp(input[1], env[count], my_strlen(input[1])) &&
        env[count][my_strlen(input[1])] == '=')
            break;
    if (!env[count])
        is_end = 1;
    env = cases(env, count, input, input_len);
    if (is_end)
        env[count + 1] = NULL;
    return env;
}
