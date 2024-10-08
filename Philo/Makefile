CC = cc 
CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g3
NAME = philo
SRCS = parsing.c philo.c threads.c monitoring.c
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

clean:
	printf "$(YELLOW)$(OBJS_DIR) removed$(END)\n"
	rm -rdf $(OBJS_DIR)

fclean: clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	rm -f $(NAME)

re: fclean all