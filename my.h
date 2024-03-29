/*
** EPITECH PROJECT, 2023
** my
** File description:
** task02 Day09
*/

#ifndef MY_H
    #define MY_H

    #include <stdlib.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/sysmacros.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <errno.h>
    #include <pwd.h>
    #include <grp.h>
    #include <time.h>
    #include <string.h>
    #include <math.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <ucontext.h>
    #include <bits/sigaction.h>
    #include <inttypes.h>
    #include <pwd.h>
    #include <grp.h>
    #include <errno.h>

void my_putchar(char c);

void my_put_nbr(long nb);

int my_putstr(char const *str);

int my_strlen(char const *str);

char *my_strcpy(char *dest, char const *src);

int my_strcmp(char *s1, char *s2);

int my_getnbr(char *str);

char *my_strchr(const char *str, int c);

char *my_strdup(char const *src);

void my_printf(const char *format, ...);

void neg_checker(int num);

char *float_inf_min(void);

char *float_inf_maj(void);

int my_strncmp(char *s1, char *s2, int n);

char *my_strcat(char *dest, const char *src);

int cell_counter(char const *str);

int is_built_in(char **input, char **env);

int change_direc(char **input);

void ttyerr(int status, int type, const char *command);

char **env_alloc(char **env);

int put_env(char **env);

char *path_is(char **env, char *command);

char **str_to_array_t(char *str);

#endif
