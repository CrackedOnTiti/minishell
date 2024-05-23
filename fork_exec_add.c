/*
** EPITECH PROJECT, 2024
** Delivery [WSL: Ubuntu]
** File description:
** fork_exec_add
*/

#include "my.h"

void ttyerr(int status, int type, const char *command)
{
    if (errno == ENOEXEC) {
        write(2, command, my_strlen(command));
        write(2, ": Exec format error. Wrong Architecture.\n", 42);
        if (type == 1)
            exit(1);
    }
    if (status == 11) {
        write(2, "Segmentation fault\n", 19);
        if (type == 1)
            exit(139);
    }
    printf("%d ; \n", status >> 8);
    if (/*status != 0 &&*/ type == 1)
        exit(status >> 8);
}
