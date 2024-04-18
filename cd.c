/*
** EPITECH PROJECT, 2024
** cd
** File description:
** just cd
*/

#include "my.h"

static int may_i_enter(char *path)
{
    if (chdir(path) != 0) {
        perror(path);
        return 1;
    }
    return 0;
}

static int go_home(void)
{
    char whereami[128];

    getcwd(whereami, 128);
    for (; my_strcmp("/home", whereami); chdir(". .")) {
        if (whereami[0] == '/')
            chdir("/home");
        if (!getcwd(whereami, 128))
            break;
    }
    return 0;
}

static int path_check(char **input)
{
    if (my_strncmp(input[0], "cd", 2) == 0 && input[1] != NULL) {
        if (may_i_enter(input[1]) == 1)
            return 1;
        return 0;
    }
    if (my_strncmp(input[0], "cd", 2) == 0 && input[1] == NULL) {
        if (go_home() == 1)
            return 1;
        return 0;
    }
    return 1;
}

int change_direc(char **input)
{
    if (path_check(input) == 1)
        return 21;
    return 0;
}
