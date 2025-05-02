# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = cub3D
LIBFT = ./libft/libft.a

# Reglas
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
