# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	cub3D

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	inc

LIBFT_DIR	:=	libft
LIBMLX		:=	MLX42
MLX42LIB	:=	$(LIBMLX)/build/libmlx42.a

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
SRC			=	main/main.c					\
				parser/init_game_struct.c	\
				parser/parsing.c			\
				parser/check_map.c			\
				parser/check_params.c		\
				parser/get_colors.c			\
				parser/get_map_array.c		\
				parser/get_textures.c		\
				parser/handle_errors.c		\
				parser/normalize_map.c		\
				parser/verify_doors.c		\
				parser/set_player.c			\
				game_loop/game_loop.c		\
				game_loop/raycast.c			\
				game_loop/raycast_utils.c	\
				game_loop/movements.c		\
				game_loop/collisions.c		\
				game_loop/minimap.c			\
				hooks/hooks.c				\
				hooks/animation.c			\

SRCDIR		= 	src
SRCS		= 	$(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= 	.obj
OBJS		= 	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR		= 	.dep
DEPS		= 	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
DEPDIRS		= 	$(DEPDIR)/main $(DEPDIR)/parser $(DEPDIR)/hooks $(DEPDIR)/game_loop

HEADERS		:=	inc/cub3D.h inc/errors.h
LIBFT_HEADERS	:=	$(LIBFT_DIR)/libft.h

MAKE		:=	Makefile

LIBS		:=	$(LIBFT_DIR)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -Wunreachable-code -Ofast -g -fsanitize=address
DFLAGS		:= 	-MMD -MP
INCLUDE		:=	-I./$(INCS) -I./$(LIBFT_DIR) -I./$(LIBMLX)/include
RM			:=	/bin/rm -fr

# -=-=-=-=-    COLORS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
DEF_COLOR := \033[0;39m

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: libft mlx $(NAME)

libft:
	@echo "$(YELLOW)Building libft...$(DEF_COLOR)"
	@make -C $(LIBFT_DIR)

mlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(YELLOW)MLX42 library not found, cloning from GitHub...$(DEF_COLOR)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi
	@if [ ! -d "$(LIBMLX)/build/" ]; then \
		echo "$(YELLOW)Building MLX42...$(DEF_COLOR)"; \
		cmake -B $(LIBMLX)/build -S $(LIBMLX) > /dev/null; \
		cmake --build $(LIBMLX)/build --target mlx42 > /dev/null; \
	fi

# -=-=-=-=-    RULES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) $(LIBFT_HEADERS) Makefile
	@mkdir -p $(@D)
	@mkdir -p $(subst $(OBJDIR),$(DEPDIR),$(@D))
	@echo "$(BLUE)Compiling $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c $< -o $@
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX42LIB)
	@echo "$(GREEN)Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEF_COLOR)"

# Forzar recompilación de libft cuando cambien sus archivos
$(LIBFT_DIR)/libft.a: $(LIBFT_HEADERS)
	@make -C $(LIBFT_DIR)

bonus: all

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJDIR) $(DEPDIR)
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME) $(LIBFT_DIR)/libft.a
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"
	@$(RM) $(LIBMLX)/build

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus libft mlx
