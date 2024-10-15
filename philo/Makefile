SRCS = philo_utils.c main.c thread_utils.c philo_actions.c

OBJ = $(SRCS:.c=.o)

CFLAGS =  -Wall -Wextra -Werror -g3 -fsanitize=thread
NAME = philo
RM = rm -f
CC = cc

all:$(NAME)

$(NAME):$(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all