# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 21:25:08 by gakarbou          #+#    #+#              #
#    Updated: 2025/02/19 17:43:23 by gakarbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/
BON_DIR = bonus/
INC_DIR = include/
OBJ_DIR = objs/

FILES = init.c philo.c utils.c parent.c errors.c outputs.c routine.c main.c
FILES_BONUS = init.c philo.c utils.c parent.c errors.c outputs.c routine.c main_bonus.c

OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR), $(FILES_BONUS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus : FLAGS += -D BONUS=1
bonus : clean $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
