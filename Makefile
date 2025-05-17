# variables
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
SRCDIR = src
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
NAME = cub3D
LIBFT = ./libft/libft.a

# Reglas
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	rm -rf $(OBJDIR)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
