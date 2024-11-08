SRCS = philo_utils.c main.c philo_actions.c life_guard.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -g3 -fsanitize=thread -Wall -Wextra -Werror
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