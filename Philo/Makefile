CC = cc 

CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g3

NAME = philo

SRCS = parsing.c philo.c threads.c monitoring.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :

fclean : clean
	rm -f $(NAME)

re : fclean all