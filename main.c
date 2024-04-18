/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** basically a terminal
*/
#include "my.h"

int terminator(char *word)
{
    if (my_strcmp(word, "exit\n") == 0)
        return 1;
    return 0;
}

static void child_killer(char *path, char *const arg[], char **env)
{
    if (execve(path, arg, env)) {
        my_printf("execve problemo\n");
        exit(84);
    }
    my_putchar('\n');
}

static void fork_exec(char *path, char *const arguments[], char **env)
{
    pid_t pid;
    int status = 0;

    pid = fork();
    if (pid == -1) {
        my_printf("fork error\n");
        exit(84);
    }
    if (pid == 0) {
        child_killer(path, arguments, env);
    } else {
        waitpid(pid, &status, 0);
        if (!isatty(0))
            ttyerr(status, 1, arguments[0]);
        ttyerr(status, 0, arguments[0]);
    }
}

int execer(const char *command, char *const arguments[], char **env)
{
    char *path = NULL;
    char *p_path = my_strdup(command);
    size_t path_length = my_strlen(path_is(env,
    (char *)command)) + my_strlen(command) + 1;

    path = (char *)malloc((1 + path_length) * sizeof(char));
    if (path == NULL) {
        my_printf("Malloc error\n");
        exit(84);
    }
    path = my_strcpy(path, path_is(env, (char *)command));
    path = my_strcat(path, (char *)command);
    if (access(path, X_OK) == 0) {
        fork_exec(path, arguments, env);
    } else {
        my_printf("%s: Command not found.\n", p_path);
    }
    free(path);
    return 0;
}

char **inputer(char *input, char **temp, char **env)
{
    extern char **environ;
    char *test = NULL;
    int size = cell_counter(input) - 1;
    int is_passed = 0;

    test = strtok(input, " \t");
    for (int i = 0; i != size; i++) {
        temp[i] = test;
        test = strtok(NULL, " \t");
    }
    temp[size] = NULL;
    env = environ;
    env = is_built_in(temp, env, &is_passed);
    if (!is_passed)
        execer(temp[0], temp, env);
    return env;
}

static int exit_mana(ssize_t length, char *input)
{
    if (length == -1) {
        if (isatty(0))
            my_printf("exit\n");
        exit(84);
    }
    if (terminator(input) == 1)
        return 1;
    return 0;
}

static void alloc_check(char **arguments)
{
    if (arguments == NULL) {
        my_printf("Unable to allocate input\n");
        exit(84);
    }
}

static void inf_lp(char *input, char **arg, char **temp, char **env)
{
    ssize_t length = 0;
    size_t bfsze = 0;

    while (1) {
        my_printf("\033[1;31mBASED\033[33m$>\033[0m ");
        length = getline(&input, &bfsze, stdin);
        if (exit_mana(length, input) == 1)
            break;
        if (input[length - 1] == '\n')
            input[length - 1] = '\0';
        length--;
        arg = malloc(sizeof(char *) * (cell_counter(input) + 1));
        temp = malloc(sizeof(char *) * (cell_counter(input) + 1));
        alloc_check(arg);
        env = inputer(input, temp, env);
        if (length + 1 == 1)
            continue;
    }
}

int main(__attribute__((unused))int argc,
    __attribute__((unused))char **argv, char **env)
{
    char *input = NULL;
    char **arguments = NULL;
    char **temp = NULL;
    char **env_cp = env_alloc(env);

    inf_lp(input, arguments, temp, env_cp);
    free(input);
    free(temp);
    free(arguments);
    return 0;
}
