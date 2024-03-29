/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** pathfinder
*/

#include "my.h"

static int conditional(DIR *name, char *command)
{
    struct dirent *entry = NULL;

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
    DIR *name = NULL;

    if (!path[0])
        return command;
    for (int i = 0; path_data[i]; i++) {
        name = opendir(path_data[i]);
        if (!name)
            return command;
        if (conditional(name, command) == 1)
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
