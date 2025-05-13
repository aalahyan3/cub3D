# include "cub3d.h"


float degree_to_radian(float deg)
{
	return (deg * (M_PI / 180.0));
}

void put_pixel_to_image(t_image *image, int x, int y, long color)
{
	int	offset = y * image->line_len + x * (image->bpp / 8);
	*(unsigned int *)(image->data + offset) = color;
}

void	draw_square(t_image *image, char c, int x, int y)
{
	int x0;
	int y0;
	long	color;

	x0 = 0;
	color = (c == '1') ? 0x808080 : 0x00FFFFFF;

	while (x0 < TILE_SIZE)
	{
		y0 = 0;
		while (y0 < TILE_SIZE)
		{
			put_pixel_to_image(image, x + x0, y + y0, color);
			y0++;
		}
		x0++;
	}
}

void init_player(t_player *player)
{
	player->x = 1;
	player->y = 1;
	player->direction_angle = 0.0f;
}


void	put_circle_pixels(t_image *image, int cx, int cy, int x, int y)
{
	put_pixel_to_image(image, cx + x, cy + y, 0x3390);
	put_pixel_to_image(image, cx - x, cy + y, 0x3390);
	put_pixel_to_image(image, cx + x, cy - y, 0x3390);
	put_pixel_to_image(image, cx - x, cy - y, 0x3390);
	put_pixel_to_image(image, cx + y, cy + x, 0x3390);
	put_pixel_to_image(image, cx - y, cy + x, 0x3390);
	put_pixel_to_image(image, cx + y, cy - x, 0x3390);
	put_pixel_to_image(image, cx - y, cy - x, 0x3390);
}

void	recursive_circle(t_image *image, int cx, int cy, int r, int x, int y)
{
	if (y > r)
		return ;
	if (x > r)
	{
		recursive_circle(image, cx, cy, r, 0, y + 1);
		return ;
	}
	if ((x * x + y * y) <= (r * r))
	{
		put_circle_pixels(image, cx, cy, x, y);
	}
	recursive_circle(image, cx, cy, r, x + 1, y);
}
void	draw_line(t_image *img, float x0, float y0, float angle, float length, int color)
{
	float	x1;
	float	y1;
	float	dx;
	float	dy;
	float	step;
	int		i;

	x1 = x0 + cosf(angle) * length;
	y1 = y0 + sinf(angle) * length;
	dx = x1 - x0;
	dy = y1 - y0;
	if (fabsf(dx) > fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	dx = dx / step;
	dy = dy / step;
	i = 0;
	while (i <= (int)step)
	{
		put_pixel_to_image(img, (int)x0, (int)y0, color);
		x0 = x0 + dx;
		y0 = y0 + dy;
		i++;
	}
}

void draw_facing_rays(t_player *player, t_image *image, int x, int y)
{
	for (int i = -FOV / 2 ; i < FOV / 2; i++)
	{
		draw_line(image, x + TILE_SIZE /2, y + TILE_SIZE / 2, degree_to_radian(player->direction_angle + i), 100,i == -1 ? 0x00FF00 : 0xFF0000);

	}
}

void draw_player_pos(t_image *image, t_player *player)
{
	int x = player->x;
	int y = player->y;
	// draw_square(image, '0', x, y);
	recursive_circle(image, x + TILE_SIZE / 2, y + TILE_SIZE / 2, 5, 0, 0);
	draw_facing_rays(player, image, x, y);
}

int update_frame(void *param)
{
	t_wrapper *wrr = (t_wrapper *)param;
	mlx_clear_window(wrr->game->mlx, wrr->game->window);
	int i;
	int j;
	i = 0;
	j = 0;
	while (wrr->map[i])
	{
		j = 0;
		while (wrr->map[i][j])
		{
			if (wrr->map[i][j] == '0' || wrr->map[i][j] == '1')
				draw_square(wrr->image, wrr->map[i][j], (j * TILE_SIZE), (i * TILE_SIZE));
			else
			{
				draw_square(wrr->image, '0', j * TILE_SIZE, i * TILE_SIZE);
			}
			j++;
		}
		i++;
	}
	draw_player_pos(wrr->image,wrr->player);
	mlx_put_image_to_window(wrr->game->mlx, wrr->game->window, wrr->image->img, 0, 0);
	return (0);
}

void move_forward(t_player *player, int factor)
{
	player->x += (cos(degree_to_radian(player->direction_angle)) * MOVE_SPEED) * factor;
	player->y += (sin(degree_to_radian(player->direction_angle)) * MOVE_SPEED) * factor;
}

void move_sidward(t_player *player, int factor)
{
	player->x += (cos(degree_to_radian((player->direction_angle - 90))) * MOVE_SPEED) * factor;
	player->y += (sin(degree_to_radian((player->direction_angle - 90))) * MOVE_SPEED) * factor;
}

int move_player(int key, void *param)
{
	t_wrapper *wrrapper = (t_wrapper *)param;
	if (key == 123)
		wrrapper->player->direction_angle = (wrrapper->player->direction_angle - 1 * ROTATION_SPEED) % 360;
	else if (key == 124)
		wrrapper->player->direction_angle = (wrrapper->player->direction_angle +  1 * ROTATION_SPEED) % 360;
	else if (key == 13)
		move_forward(wrrapper->player, 1);
	else if (key == 1)
		move_forward(wrrapper->player, -1);
	else if (key == 0)
		move_sidward(wrrapper->player, 1);
	else if (key == 2)
		move_sidward(wrrapper->player, -1);
	else if (key == 53)
		exit(1);
	return (0);
}

int main()
{
	char *map[11] ={
		"1111111111",
		"1010101011",
		"1000000001",
		"1110100001",
		"1000000001",
		"1010101011",
		"100P000001",
		"1000000001",
		"1000000001",
		"1111111111",
		NULL
	};
	t_player player;
	t_game	game;
	t_image	image;
	init_player(&player);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WINDOW_W, WINDOW_H, "whatever");
	image.img = mlx_new_image(game.mlx, 10 * TILE_SIZE ,10 * TILE_SIZE);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.line_len, &image.endian);
	t_wrapper wrapper;
	wrapper.game = &game;
	wrapper.player = &player;
	wrapper.image = &image;
	wrapper.map = map;
	mlx_loop_hook(game.mlx, update_frame, &wrapper);
	mlx_hook(game.window,2, 0,  move_player, &wrapper);
	mlx_loop(game.mlx);
}