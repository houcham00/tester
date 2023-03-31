##
## EPITECH PROJECT, 2022
## 101PONG_MAKEFILE
## File description:
## makefile to compile and create the binary
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	test

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	all fclean
