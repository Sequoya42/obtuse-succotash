#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/12 17:20:35 by rbaum             #+#    #+#              #
#    Updated: 2015/10/11 18:42:41 by rbaum            ###   ########.fr        #
#                                                                              #
#******************************************************************************#


.PHONY:			all, libft, clean, fclean, re

CC =			gcc

CFLAG =			-Wall -Wextra -Werror

NAME =			21sh

SRC_PATH =		./src/

OBJ_PATH =		./obj/

LIBFT_PATH =	./libft/

TERMFT_PATH = 	./libtermft/

INC_PATH =		./inc/

SRC_NAME =		main.c			ft_prompt.c		ft_gest_cmd.c		ft_env.c\
				ft_sub_env.c	ft_short_cmd.c	ft_cd.c				\
						move_line.c			get_env.c\


OBJ_NAME =		$(SRC_NAME:.c=.o)

LIBFT_NAME =	libft.a

TERMFT_NAME = 	termft.a

INC_NAME =		ft_sh.h\

SRC =			$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ =			$(addprefix $(OBJ_PATH),$(OBJ_NAME))

LIBFT =			$(addprefix $(LIBFT_PATH),$(LIBFT_NAME))

TERMFT =		$(addprefix $(TERMFT_PATH), $(TERMFT_NAME))

INC =			$(addprefix $(INC_PATH),$(INC_NAME))

INCLIBFT = 		$(LIBFT_PATH)inc

INCTERMFT = 	$(TERMFT_PATH)inc

LIBFT_FLAG = 	-L$(LIBFT_PATH) -lft

TERMFT_FLAG = 	-L$(TERMFT_PATH) -ltermft -ltermcap

INC_ALL		=	-I$(INC_PATH) -I$(INCLIBFT) -I$(INCTERMFT)

all:			libft $(NAME) 

$(NAME):		$(OBJ)
				@$(CC) $(LIBFT_FLAG) $(TERMFT_FLAG) -o $@ $^
				@echo "Shell created"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c $(INC)
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAG) $(INC_ALL) -o $@ -c $<

libft:			$(LIBFT)

$(LIBFT):		$(LIBFT_PATH)
				@make -C $(LIBFT_PATH)

$(TERMFT):		$(TERMFT_PATH)
				@make -C $(TERMFT_PATH)

clean:
				@make -C $(LIBFT_PATH) clean
				@make -C $(TERMFT_PATH) clean
				@rm -f $(OBJ)

fclean:			
				@rm -f $(OBJ)
				@make -C $(LIBFT_PATH) fclean
				@make -C $(TERMFT_PATH) fclean
				@rm -f $(NAME)

re: 			fclean all
