# Program name
NAME	= cube3D

# Compiler
CC		= cc
CFLAGS  = -g -Wall -Wextra -Werror
MLX_FLAGS = -L/usr/X11/lib -lXext -lX11 -lm

# Libft
LIBFT_PATH	= libft_based/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Minilibx
MINILIBX_PATH	= minilibx-linux/
MINILIBX_NAME	= libmlx_Linux.a
MINILIBX		= $(MINILIBX_PATH)$(MINILIBX_NAME)

# Includes
INC			=	-I ./includes/\
				-I ./libft_based/

# Sources  
SRC_DIR		= src/
SRC			= main.c \

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Default target
all: $(OBJ_PATH) $(LIBFT) $(MINILIBX) $(NAME)

# Rule to compile object files
$(OBJ_PATH)%.o: $(SRC_DIR)%.c
	@printf "\r\033[KCompiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Create object directory if it doesn't exist
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

# Build libft
$(LIBFT):
	@echo "Making libft..."
	@make -C $(LIBFT_PATH) --no-print-directory
	@echo "done"

# Build minilibx
$(MINILIBX):
	@echo "Making minilibx..."
	@make -C $(MINILIBX_PATH) --no-print-directory
	@echo "done"

# Compile the program
$(NAME): $(OBJS)
	@echo ""
	@echo "Compiling cube3D..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) $(MLX_FLAGS) $(INC)
	@echo "cube3D ready."

# Clean object files
clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH) --no-print-directory

# Clean everything
fclean: clean
	@echo "Removing cube3D..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all re clean fclean
