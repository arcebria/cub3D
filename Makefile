# variables
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBFT_DIR := libft
LIBMLX := MLX42
HEADERS := -I ./include -I $(LIBMLX)/include/MLX42/MLX42.h -I $(LIBFT_DIR)
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT_DIR)/libft.a
SRCDIR = src/parser src/raycast src/main
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Reglas
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(LIBMLX)/build/libmlx42.a Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(LIBMLX)/build/libmlx42.a:
	cmake -B $(LIBMLX)/build -S $(LIBMLX) > /dev/null
	cmake --build $(LIBMLX)/build --target mlx42 > /dev/null

clean:
	rm -rf $(OBJDIR)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
