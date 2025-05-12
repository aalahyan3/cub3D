# include "cub3d.h"

void put_pixel_to_image(t_image *image, int x, int y, long color)
{
	int offset = y * image->line_len + x * (image->bpp / 8);
	*(unsigned int *)(image->data + offset) = color;
}

void draw_square(t_image *image, char c, int x, int y)
{
	int x0;
	int y0;
	long color;

	x0 = 0;
	color = (c == '1') ? 0x808080 : 0x00FFFFFF;  // Gray for walls, white for spaces

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

int main()
{
	char *map[11] ={
		"11111111110",
		"10101010101",
		"10000000001",
		"11101000000",
		"10000000000",
		"10101010101",
		"10000000001",
		"10000000001",
		"10000000001",
		"11111110001",
		NULL
	};

	t_player player;
	t_game	game;
	t_image	image;

	init_player(&player);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 11 * TILE_SIZE, 10 * TILE_SIZE, "whatever");

	// Create image for drawing
	image.img = mlx_new_image(game.mlx, 11 * TILE_SIZE, 10 * TILE_SIZE);
	image.data = mlx_get_data_addr(image.img, &image.bpp, &image.line_len, &image.endian);

	// Loop through the map to draw each square
	int i = 0;
	int j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			draw_square(&image, map[i][j], j * TILE_SIZE, i * TILE_SIZE);  // Reverse the order
			j++;
		}
		i++;
	}

	// Display image in the window
	mlx_put_image_to_window(game.mlx, game.window, image.img, 0, 0);

	// Start the MLX loop
	mlx_loop(game.mlx);

	return 0;
}
