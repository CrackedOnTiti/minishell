/*
** EPITECH PROJECT, 2023
** print_f
** File description:
** print_f.c
*/

#include "../my.h"

static void oct_uns(const char **format, va_list list, long o, long u)
{
    long i = 1;
    long oct = 0;

    if (**format == 'o') {
        o = va_arg(list, long);
        for (; o != 0; o /= 8) {
            oct += (o % 8) * i;
            i *= 10;
        }
        my_put_nbr(oct);
    }
    if (**format == 'u') {
        u = va_arg(list, long int);
        my_put_nbr(u);
    }
}

void else_loop(long nb, char *hex_list, char *hex)
{
    int i;
    int j;

    for (i = 0; nb > 0; i = i + 1) {
        hex[i] = hex_list[nb % 16];
        nb /= 16;
    }
    for (j = i - 1; j >= 0; j--) {
        my_putchar(hex[j]);
    }
}

void hex(const char **format, va_list list)
{
    char *hex_list = "0123456789ABCDEF";
    long nb;
    char hex[16];

    if (**format == 'X') {
        nb = va_arg(list, long);
        if (nb < 0) {
            my_putchar('-');
            nb *= -1;
        }
        if (nb < 16) {
            my_putchar(hex_list[nb]);
        } else
        else_loop(nb, hex_list, hex);
    }
}

void hex2(const char **format, va_list list)
{
    char *hex_list = "0123456789abcdef";
    long nb;
    char hex[16];

    if (**format == 'x') {
        nb = va_arg(list, long);
        if (nb < 0) {
            my_putchar('-');
            nb *= -1;
        }
        if (nb < 16) {
            my_putchar(hex_list[nb]);
        } else {
            else_loop(nb, hex_list, hex);
        }
    }
}

static void exp_shortener(double num, int av_vir, double ap_vir, int precision)
{
    neg_checker(num);
    av_vir = (int)num;
    ap_vir = num - av_vir;
    my_put_nbr(av_vir);
    my_putchar('.');
    ap_vir -= (int)ap_vir;
    for (int i = 0; i < precision; i++) {
        ap_vir *= 10;
    }
    my_put_nbr((int)ap_vir);
}

int exp_float(const char **format, va_list list)
{
    double num = va_arg(list, double);
    double ap_vir = 0;
    int precision = 6;
    int av_vir = 0;

    switch (**format) {
        case 'F':
            if (num >= 2147483647 || num <= -2147483647)
                return my_putstr(float_inf_maj());
            exp_shortener(num, av_vir, ap_vir, precision);
            break;
        case 'f':
            if (num >= 2147483647 || num <= -2147483647)
                return my_putstr(float_inf_min());
            exp_shortener(num, av_vir, ap_vir, precision);
            break;
    }
    return 0;
}

static void recursive_hex_for_p(long point)
{
    char *hex_list = "0123456789abcdef";
    long nb = point;
    char hex[16];
    int i = 0;

    if (nb < 0) {
        my_putchar('-');
        nb *= -1;
    }
    if (nb < 16) {
        my_putchar(hex_list[nb]);
    } else {
        for (i = 0; nb > 0; i = i + 1) {
            hex[i] = hex_list[nb % 16];
            nb /= 16;
        }
        for (int j = i - 1; j >= 0; j--) {
            my_putchar(hex[j]);
        }
    }
}

static void point_numchar(const char **format, va_list list, int *i)
{
    int *n;
    void *p;
    long point;

    if (**format == 'n') {
        n = va_arg(list, int *);
        *n = *i;
    }
    if (**format == 'p') {
        p = va_arg(list, void *);
        point = ((long)p);
        my_putstr("0x");
        recursive_hex_for_p(point);
    }
}

static void c_s_d(const char **format, va_list list)
{
    char c;
    char *s;
    int d;

    if (**format == 'c') {
        c = va_arg(list, int);
        my_putchar(c);
    }
    if (**format == 's') {
        s = va_arg(list, char *);
        my_putstr(s);
    }
    if (**format == 'd' || **format == 'i') {
        d = va_arg(list, int);
        my_put_nbr(d);
    }
    if (**format == '%') {
        my_putchar('%');
    }
}

void my_printf(const char *format, ...)
{
    int i = 0;
    va_list list;

    va_start(list, format);
    for (; *format; format++) {
        if (*format != '%') {
            my_putchar(*format);
        } else {
            format++;
            c_s_d(&format, list);
            oct_uns(&format, list, 0, 0);
            hex(&format, list);
            hex2(&format, list);
            exp_float(&format, list);
            point_numchar(&format, list, &i);
        }
        i++;
    }
    va_end(list);
}
