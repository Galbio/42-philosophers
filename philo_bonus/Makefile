# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 02:33:53 by gakarbou          #+#    #+#              #
#    Updated: 2025/01/31 03:09:06 by gakarbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = objs/

FILES = main.c utils.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
