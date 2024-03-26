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
    char *path;
    size_t path_length = my_strlen("/bin/") + my_strlen(command) + 1;

    path = (char *)malloc(path_length * sizeof(char));
    if (path == NULL) {
        my_printf("Malloc error\n");
        exit(84);
    }
    my_strcpy(path, "/bin/");
    my_strcat(path, command);
    if (access(path, X_OK) == 0) {
        fork_exec(path, arguments, env);
    } else {
        my_printf("%s: Command not found.\n", command);
    }
    free(path);
    return 0;
}

void basic_err(char *input, int argc)
{
    if (input == NULL) {
        my_printf("Unable to allocate input\n");
        exit(84);
    }
    if (argc != 1) {
        my_printf("No other arguments other than : ./mysh\n");
        exit(84);
    }
}

int inputer(char *input, char **temp, char **env)
{
    extern char **environ;
    char *test = NULL;
    int size = cell_counter(input) - 1;
    int return_v = 0;

    test = strtok(input, " \t");
    for (int i = 0; i != size; i++) {
        temp[i] = test;
        test = strtok(NULL, " \t");
    }
    temp[size] = NULL;
    env = environ;
    return_v = is_built_in(temp);
    if (return_v == 69)
        return 1;
    if (return_v == 1)
        return 0;
    execer(temp[0], temp, env);
    return 0;
}

static int exit_mana(ssize_t length, char *input)
{
    if (length == -1) {
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
    size_t bfsze = 128;

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
        if (length + 1 == 1 || inputer(input, temp, env) == 1)
            continue;
    }
}

int main(int argc, __attribute__((unused))char **argv, char **env)
{
    char *input = (char *)malloc(128 * sizeof(char));
    char **arguments = NULL;
    char **temp = NULL;

    basic_err(input, argc);
    inf_lp(input, arguments, temp, env);
    free(input);
    free(temp);
    free(arguments);
    return 0;
}
