/*
** EPITECH PROJECT, 2023
** Delivery [WSL: Ubuntu]
** File description:
** inf_error.c
*/
#include "../my.h"

char *float_inf_min(void)
{
    return "inf";
}

char *float_inf_maj(void)
{
    return "INF";
}

void neg_checker(int num)
{
    if (num < 0) {
            my_putchar('-');
            num *= -1;
        }
}
