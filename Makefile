##
## EPITECH PROJECT, 2023
## Setting_up
## File description:
## Makefile
##

SRC = 	printf/print_f.c \
		printf/exp_float_opti.c \
		custom_str_to_array.c \
		main.c \
		built_in.c \
		cd.c \
		fork_exec_add.c \
		main_env_alloc.c \
		env_prnt.c \
		pathfinder.c \
		my_str_to_word_array_twodots.c \
		setter.c \
		my_put_nbr.c \
		my_putchar.c \
		my_putstr.c	\
		my_strlen.c	\
		my_strcpy.c	\
		my_strcmp.c	\
		my_strcat.c	\
		my_strncmp.c \
		my_getnbr.c	\
		my_strchr.c \
		my_strdup.c

OBJ = $(SRC:.c=.o)

EXECUTABLE = mysh

CFLAGS = -Wall -Wextra -g3

$(EXECUTABLE): $(OBJ)
	$(CC) -lm -o $@ $(OBJ)

all: $(EXECUTABLE)

clean:
	rm -f $(OBJ) $(EXECUTABLE)

fclean: clean
	rm -f $(NAME)

re:	fclean	all
