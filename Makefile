# variables
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBFT_DIR := libft
LIBMLX := MLX42
HEADERS := -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT_DIR)
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT_DIR)/libft.a
SRCDIR = src/parser src/raycast src/main
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Reglas
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(LIBMLX)/build/libmlx42.a Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(LIBMLX)/build/libmlx42.a: $(LIBMLX)
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42 repository..."; \
        git clone --recurse-submodules https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
    fi
		rm -rf $(LIBMLX)/build
		cmake -B $(LIBMLX)/build -S $(LIBMLX) > /dev/null
		cmake --build $(LIBMLX)/build --target mlx42 > /dev/null

$(LIBMLX):
    git clone --recurse-submodules https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

clean:
	rm -rf $(OBJDIR)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBMLX)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
