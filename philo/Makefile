SRCS	= main.c philo_utils.c

OBJ = $(SRCS:.c=.o)

CFLAGS =#-Wall -Wextra -Werror
NAME = philo
RM = rm -f
CC = cc

all:$(NAME)

$(NAME):$(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all