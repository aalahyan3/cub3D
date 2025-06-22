SRC_RC = raycasting/raycasting.c raycasting/moving_and_hook.c raycasting/raycasting_inite.c raycasting/raycasting_utilis.c  raycasting/vertical_casting.c raycasting/collision.c raycasting/horizontal_casting.c raycasting/cleanup.c raycasting/maping_textuers.c
SRC_PS = parsing/parse.c parsing/clear_map.c parsing/fill_map_data.c parsing/map_validation.c parsing/set_attribute.c parsing/map_reading.c parsing/utils.c parsing/map_validation_2.c
SRC_ROOT = main.c load_textures.c
SRC_BONUS = _bonus/minimap_bonus.c _bonus/get_animation_bonus.c _bonus/mouse_handler_bonus.c 
OBJ = $(SRC_RC:.c=.o) $(SRC_PS:.c=.o) $(SRC_ROOT:.c=.o) $(SRC_BONUS:.c=.o)
NAME = cub3D
HEADERS = raycasting/all_data_struct.h raycasting/raycasting.h parsing/parsing.h _bonus/_bonus.h cub3d.h
FLAGS = #-wall -Wextra -Werror
CC = cc

all bonus: libft $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -lft -Llibft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

libft:
	make -C libft

%.o: ./%.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
	make clean -C  libft

fclean: clean
	rm -f $(NAME)
	make fclean -C  libft

re: fclean all

.PHONY: libft clean
