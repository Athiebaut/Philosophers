NAME = philo
NAME_B = philo_bonus
SRC_DIR = philo_m/srcs
SRC_DIR_B = philo_b/srcs
OBJ_DIR = objs
OBJ_DIR_B = objs_b
SRCS =  main.c \
	check_death.c \
	check_args.c \
	utils.c \
	routine.c

SRCS_B =  main_bonus.c \
	check_args_bonus.c \
	routine_bonus.c \
	utils_bonus.c

LIBFT = ./Libft/libft.a
SRCS := $(SRCS:%=$(SRC_DIR)/%)
SRCS_B := $(SRCS_B:%=$(SRC_DIR_B)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_B := $(SRCS_B:$(SRC_DIR_B)/%.c=$(OBJ_DIR_B)/%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
DIR_DUP     = mkdir -p $(@D)

all : $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR_B)/%.o:$(SRC_DIR_B)/%.c
	$(DIR_DUP)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -C Libft
	$(CC) $(FLAGS) $(OBJS) -o $@

bonus : $(OBJS_B)
	make -C Libft
	$(CC) $(FLAGS) $(OBJS_B) ${LIBFT} -o ${NAME_B}

clean :
	make -j clean -C ./Libft
	rm -f $(OBJS)
	rm -f $(OBJS_B)
	rm -rf objs
	rm -rf objs_b

fclean : clean
	make -j fclean -C ./Libft
	rm -f philo
	rm -f philo_bonus

re : fclean
	make all

.PHONY : all bonus clean fclean re