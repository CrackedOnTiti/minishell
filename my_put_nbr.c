/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** task07 Day03
*/
#include "my.h"

void my_putchar2(char c)
{
    write(1, &c, 1);
}

void my_put_nbr(long nb)
{
    long n = 0;

    if (nb < 0){
        my_putchar2('-');
        nb = -nb;
    } else if (nb < 10) {
        my_putchar2(nb + '0');
    }
    if (nb > 9) {
        my_put_nbr(nb / 10);
        n = nb % 10;
        my_putchar2(n + '0');
    }
}
