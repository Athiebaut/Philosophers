NAME = philo
SRC_DIR = Philosophers/srcs
OBJ_DIR = objs
SRCS =  main.c \
	check_death.c \
	check_args.c \
	utils.c \
	routine.c

LIBFT = ./Libft/libft.a
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g3
DIR_DUP     = mkdir -p $(@D)

all : $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -C Libft
	$(CC) $(FLAGS) $(OBJS) ${LIBFT} $(INC_LIBFT) -o $@

clean :
	make -j clean -C ./Libft
	rm -f $(OBJS)
	rm -rf objs

fclean : clean
	make -j fclean -C ./Libft
	rm -f philo

re : fclean
	make all

.PHONY : all bonus clean fclean re