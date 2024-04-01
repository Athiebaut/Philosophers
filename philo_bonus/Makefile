NAME = philo_bonus
SRC_DIR = srcs
OBJ_DIR = objs
SRCS =  main_bonus.c \
	check_args_bonus.c \
	routine_bonus.c \
	utils_bonus.c

LIBFT = ../Libft/libft.a
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror 
DIR_DUP     = mkdir -p $(@D)

all : $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -C ../Libft
	$(CC) $(FLAGS) $(OBJS) -o $@

clean :
	make -j clean -C ../Libft
	rm -f $(OBJS)
	rm -rf objs

fclean : clean
	make -j fclean -C ../Libft
	rm -f philo_bonus

re : fclean
	make all

.PHONY : all bonus clean fclean re