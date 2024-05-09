NAME = philo

SRCS = ./dinner.c ./init.c ./main.c ./monitor.c\
		./routine.c ./utils.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread

CC = cc

INCLUDE = ./philo.h

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)