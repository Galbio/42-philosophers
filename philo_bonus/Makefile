# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 21:25:08 by gakarbou          #+#    #+#              #
#    Updated: 2025/02/04 22:40:28 by gakarbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror 

SRC_DIR = src/
BON_DIR = bonus/
INC_DIR = include/
OBJ_DIR = objs/

FILES = main.c utils.c utils2.c
FILES_BONUS = utils.c routine.c init.c supervisor.c utils2.c main_bonus.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
BONUS_SRCS = $(addprefix $(SRC_DIR), $(FILES_BONUS))
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(FILES_BONUS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus : FLAGS += -D BONUS=1
bonus : $(BONUS_OBJS)
	$(CC) $(FLAGS) $(BONUS_OBJS) -D BONUS=1 -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
