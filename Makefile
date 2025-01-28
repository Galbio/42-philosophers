NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = objs/

FILES = main.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

tester :
	@echo "c bon"
