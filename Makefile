SRC_RC = raycasting/raycasting.c raycasting/moving_and_hook.c raycasting/raycasting_inite.c raycasting/raycasting_utilis.c  raycasting/vertical_casting.c raycasting/horizontal_casting.c
SRC_PS = parsing/parse.c parsing/clear_map.c parsing/fill_map_data.c parsing/map_validation.c raycasting/maping_textuers.c
SRC_ROOT = main.c load_textures.c
SRC_BONUS = minimap/minimap.c animation/get_animation.c mouse_handler/mouse_handler.c
OBJ = $(SRC_RC:.c=.o) $(SRC_PS:.c=.o) $(SRC_ROOT:.c=.o) $(SRC_BONUS:.c=.o)
NAME = cub3d
FLAGS = -fsanitize=address#-Wall -Wextra -Werror
CC = cc

all: libft $(NAME)

$(NAME): $(OBJ) cub3d.h
	$(CC) $(FLAGS) $(OBJ) -lft -Llibft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

libft:
	make -C libft

raycasting/%.o: raycasting/%.c raycasting/raycasting.h
	$(CC) $(FLAGS) -c $< -o $@
parsing/%.o: parsing/%.c parsing/parsing.h
	$(CC) $(FLAGS) -c $< -o $@
minimap/%.o: parsing/%.c minimap/minimap.h
	$(CC) $(FLAGS) -c $< -o $@
animation/%.o: animation/%.c animation/animation.h
	$(CC) $(FLAGS) -c $< -o $@
./%.o: ./%.c cub3d.h
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
	make clean -C  libft

fclean: clean
	rm -f $(NAME)
	make fclean -C  libft

re: fclean all

.PHONY: libft clean
