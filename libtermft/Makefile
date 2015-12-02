#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/11 17:48:47 by rbaum             #+#    #+#              #
#    Updated: 2015/10/20 15:13:26 by rbaum            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

CFLAG = -Wall -Werror -Wextra

NAME = libtermft.a

INC_PATH =	./inc/

OBJ_PATH = ./obj/

SRC_PATH = ./src/

SRC_NAME = 	key_events.c	modif_term.c		move.c\
			move_control.c	move_direction.c\
			print_front.c		print_list.c\
			short_func.c	signal.c key_events.c\

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = term_related.h

SRC =		$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ =		$(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC =		$(addprefix $(INC_PATH),$(INC_NAME))

INCLIBFT =  ../libft/inc

SELECT_FLAG =	-ltermcap

INC_ALL = -I$(INC_PATH) -I$(INCLIBFT)

all: 		$(NAME)

$(NAME): 	$(OBJ)
			@ar rc $@ $^ 
			@echo "compile done !"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
			@mkdir -p $(OBJ_PATH)
			@$(CC) $(CFLAG) $(INC_ALL) -o $@ -c $<

clean:
			@rm -rf $(OBJ)
			@echo "clean done !"

fclean:		clean
			@rm -rf $(NAME)
			@echo "fclean done !"

re: 		fclean all