SRC =	main.c \
utils.c \
fctmlx.c

NAME = Fractol

MLX_DIR = mlx
MLX = libmlx.dylib
CC = clang

CFLAGS = -g

OBJ = $(SRC:.c=.o)
DPD = $(SRC:.c=.d)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l mlx
		@install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)
		@echo $(NAME) : Created !

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_DIR)/$(MLX) | .gitignore
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(OBJ)

fclean:	clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

-include $(DPD)