# ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# define TILE_SIZE 50


# define FOV 60
# define MOVE_SPEED 3
# define ROTATION_SPEED 3
# define WINDOW_H 800
# define WINDOW_W 1000

typedef struct s_image
{
	void	*img;
	char	*data;
	int	bpp;
	int	width;
	int	height;
	int	line_len;
	int	endian;
	int x;
	int y;
}	t_image;

typedef struct s_game
{
	void	*mlx;
	void	*window;
}	t_game;

typedef struct s_player{
	int	x;
	int	y;
	int direction_angle;
	int f;
}	t_player;
typedef struct s_wrapper
{
	t_game *game;
	t_player *player;
	t_image *image;
	char	**map;
}	t_wrapper;
# endif