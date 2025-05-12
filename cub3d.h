# ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 50

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
	float direction_angle;
}	t_player;

# endif