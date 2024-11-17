SRCS = philo_utils.c main.c philo_actions.c life_guard.c extra_utils.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3
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

.SECONDARY:$(OBJ)