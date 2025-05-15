SRC = raycasting.c
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
