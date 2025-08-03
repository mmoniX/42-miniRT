CC = cc
CFLAGS = -Wall -Wextra -Werror
VAL = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

SRC = src/main.c src/check.c src/colour.c src/init.c src/light.c src/parse_obj.c \
	 src/parse_utils.c src/render.c src/ray_tracing.c src/hit.c src/utils.c \
	 src/vector.c src/vector2.c src/cylinder.c src/shadow.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = lib/libFT
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = lib/MLX42
MLX = $(MLX_DIR)/build/libMLX42.a

HEADERS := -I ./inc -I $(MLX_DIR)/include/
LIBS := -L$(LIBFT_DIR) -lft -ldl -lglfw -pthread -lm

NAME = miniRT

all: $(MLX) $(LIBFT) $(NAME)

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX): $(MLX_DIR)
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make --no-print-directory -C $(MLX_DIR)/build -j4

$(LIBFT_DIR):
	git clone https://github.com/mmoniX/libFT.git $(LIBFT_DIR)

$(LIBFT): $(LIBFT_DIR)
	@echo "\033[34m🔄 Loading....\033[0m"
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(LIBS)
	@echo "\033[32m🚀 Program is ready to execute\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir	-p	$(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@echo "\033[31mProgram removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)
	@rm -f $(LIBFT)

re: fclean all

valgrind: $(NAME)
	$(VAL) ./$(NAME)

.PHONY: all clean fclean re valgrind