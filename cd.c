/*
** EPITECH PROJECT, 2024
** cd
** File description:
** just cd
*/

#include "my.h"

static int go_back(char **prev_pwd)
{
    if (!*prev_pwd) {
        write(2, ": Failed to change directory.\n", 31);
        return 0;
    }
    chdir(*prev_pwd);
    *prev_pwd = getcwd(*prev_pwd, 128);
    return 0;
}

static int may_i_enter(char *path, char **prev_pwd)
{
    *prev_pwd = getcwd(*prev_pwd, 128);
    if (chdir(path) != 0) {
        perror(path);
        return 1;
    }
    return 0;
}

static int go_home(char **prev_pwd)
{
    char whereami[128];

    getcwd(whereami, 128);
    *prev_pwd = getcwd(*prev_pwd, 128);
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
    static char *prev_pwd = NULL;

    if (my_strncmp(input[0], "cd", 2) == 0 && (input[1] == NULL ||
        !my_strcmp(input[1], "~"))) {
        go_home(&prev_pwd);
        return 0;
    }
    if (my_strncmp(input[0], "cd", 2) == 0 && !my_strcmp(input[1], "-")) {
        go_back(&prev_pwd);
        return 0;
    }
    if (my_strncmp(input[0], "cd", 2) == 0 && input[1] != NULL) {
        if (may_i_enter(input[1], &prev_pwd) == 1)
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
