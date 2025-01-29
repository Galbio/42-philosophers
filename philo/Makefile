# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 21:25:08 by gakarbou          #+#    #+#              #
#    Updated: 2025/01/29 22:38:47 by gakarbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/
BON_DIR = bonus/
INC_DIR = include/
OBJ_DIR = objs/

FILES = main_bonus.c utils.c routine.c init_bonus.c supervisor.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus : $(BONUS_OBJS)
	$(CC) $(FLAGS) $(BONUS_OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
