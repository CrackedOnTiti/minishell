/*
** EPITECH PROJECT, 2023
** for my navy
** File description:
** my_str_to_word_array.c
*/

#include "my.h"

static int is_it_alpha_t(char c)
{
    if (c != ':')
        return (1);
    return (0);
}

static int count_words_t(char *str)
{
    int word = 0;
    int i = 0;
    int nb_words = 0;

    while (str[i]) {
        if (word == 0 && is_it_alpha_t(str[i]) == 1) {
            word = 1;
            nb_words++;
        }
        if (word == 1 && is_it_alpha_t(str[i]) == 0)
            word = 0;
        i++;
    }
    return (nb_words);
}

static void dup_n_car_t(char *new_str, char *str, int begin, int end)
{
    int i = 0;

    while (begin <= end) {
        new_str[i] = str[begin];
        begin = begin + 1;
        i = i + 1;
    }
    new_str[i] = '\0';
}

static void save_words_t(char **tab, char *str, int nb_words)
{
    int i = 0;
    int begin = 0;
    int word_cur = 0;

    while (word_cur < nb_words) {
        while (str[i] && is_it_alpha_t(str[i]) == 0)
            i++;
        begin = i;
        while (str[i] && is_it_alpha_t(str[i]) == 1)
            i++;
        tab[word_cur] = (char *) malloc(sizeof(char) * ((i - 1) - begin + 2));
        dup_n_car_t(tab[word_cur], str, begin, i - 1);
        i++;
        word_cur++;
    }
}

char **str_to_array_t(char *str)
{
    int nb_words = 0;
    char **tab = NULL;

    nb_words = count_words_t(str);
    tab = malloc(sizeof(char *) * (nb_words + 1));
    save_words_t(tab, str, nb_words);
    tab[nb_words] = NULL;
    return (tab);
}
