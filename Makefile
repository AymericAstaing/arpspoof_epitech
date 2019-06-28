##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## NWP_myarpspoof_2018
##

CFLAGS  +=      -Wall -Werror -Wextra
CFLAGS  +=      -I./include -g3

SRC     +=      main.c					\
				src/init.c				\
				src/receiver.c			\
				src/spoof.c				\
				src/output.c			\
				src/utils.c				\
				src/broadcast.c

NAME    =       myARPspoof

all:            $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(CFLAGS)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: clean fclean re all
