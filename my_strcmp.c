/*
** EPITECH PROJECT, 2023
** B-CPE-110-TLS-1-1-organized-jules.de-rus [WSL: Ubuntu]
** File description:
** my_strcmp.c
*/

int my_strcmp(char *s1, char *s2)
{
    for (; *s1 != '\0' && *s2 != '\0' && *s1 == *s2; s1++)
        s2++;
    if (*s1 == *s2)
        return 0;
    else if (*s1 < *s2)
        return -1;
    else
        return 1;
    return 0;
}
