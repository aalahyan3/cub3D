SRC = main.c raycasting.c moving_and_hook.c raycasting_inite.c raycasting_utilis.c  vertical_casting.c horizontal_casting.c
OBJ = $(SRC:.c=.o)
NAME = cub3d
FLAGS = -Wall -Wextra -Werror -g3
CC = cc

all: $(NAME)

$(NAME): $(OBJ) raycasting.h
	$(CC) $(FLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c raycasting.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
