# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 21:25:08 by gakarbou          #+#    #+#              #
#    Updated: 2025/02/21 21:54:22 by gakarbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror

RESET = \033[0m
GREEN = \033[0;32m
YELLOW = \033[1;93m
ORANGE = \033[38;5;208m
RED = \033[1;31m
BLUE = \033[1;94m
CYAN = \033[0;36m
MAGENTA = \033[0;35m

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = objs/

FILES = init.c philo.c utils.c parent.c errors.c outputs.c routine.c main.c
FILES_BONUS = init.c philo.c utils.c parent.c errors.c outputs.c routine.c main_bonus.c

OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR), $(FILES_BONUS:.c=.o))

all : $(NAME)

newline :
	@echo ""

$(NAME) : $(OBJS)
	@echo ""
	@echo -n "$(YELLOW)[Linking] => "
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Program Compiled!$(RESET)"

bonus : FLAGS += -D BONUS=1
bonus : clean newline $(OBJS_BONUS)
	@echo ""
	@echo -n "$(YELLOW)[Linking] => "
	@$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME)
	@echo "$(YELLOW)Program Compiled!$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo -n "$(GREEN)[Compiling] => "
	@$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "$@$(RESET)"

clean :
	@echo "$(RED)[Deleting] => $(OBJ_DIR)$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "$(RED)[Deleting] => $(NAME)$(RESET)"
	@rm -f $(NAME)

re : fclean newline all
