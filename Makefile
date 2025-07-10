NAME = philo

SRC = main.c init.c threads.c monitor.c routine.c utils.c

MANPATH = $(addprefix ./src/, $(SRC))

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

HEADER = ./src/philo.h 

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@$(CC) $(FLAGS) -o $(NAME) $(MANPATH)

clean: 
		@rm -f $(NAME)

fclean: clean

re: fclean all