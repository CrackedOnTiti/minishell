/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** pathfinder
*/

#include "my.h"

void print_arr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        my_printf("%s\n", arr[i]);
}

static int conditional(char *command, char *path)
{
    struct dirent *entry = NULL;
    DIR *name = NULL;

    name = opendir(path);
    if (!name)
        return 2;
    entry = readdir(name);
    while (entry != NULL) {
        if (my_strcmp(entry->d_name, command) == 0)
            return 1;
        entry = readdir(name);
    }
    return 0;
}

static char *data_input(char *path, char *command, int *error)
{
    char **path_data = str_to_array_t(path);
    int return_v = 0;

    if (!path[0])
        return command;
    for (int i = 0; path_data[i]; i++) {
        return_v = conditional(command, path_data[i]);
        if (return_v == 2)
            return command;
        if (return_v == 1)
            return path_data[i];
    }
    *error = 1;
    return NULL;
}

static char *conditional2(char *command, char *path, char *env, int error)
{
    path = data_input(env + 5, command, &error);
    if (!error) {
        path = my_strcat(path, "/");
        return path;
    } else
        return NULL;
    return 0;
}

char *path_is(char **env, char *command)
{
    char *path = NULL;
    int error = 0;

    for (int i = 0; env[i]; i++)
        if (!my_strncmp("PATH=", env[i], 5))
            return conditional2(command, path, env[i], error);
    return "/bin/";
}
