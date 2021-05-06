NAME = philo_two
SRCS = external.c main.c ph_do.c \
	simulation.c utils_00.c utils_01.c \
	utils_02.c utils_03.c 
CC = gcc
FLAGS = -pthread -g
HEADER = ./
DIR_O = objs
DIR_S = ./
OBJS = $(addprefix $(DIR_O)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/philo_two.h
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

clean:
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean re all clean