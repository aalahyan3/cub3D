/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/17 14:30:12 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	draw_floor_and_ceiling(void *img, int ceiling_color, int floor_color)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (x < win_width)
		{
			if (y < win_height / 2)
				my_mlx_pixel_put(img, x, y, ceiling_color);
			else
				my_mlx_pixel_put(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void draw(t_all_data *data)
{
	clear_image(&data->img);
	draw_floor_and_ceiling(&data->img, data->mape->ceil_color, data->mape->floor_color);
	start_casting(&data->player, &data->img, data->mape,data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}


int main(int ac, char **av)
{
	t_img img;
	t_player player;
	t_all_data data;
	unsigned int *wall_textuers;
	data.mape = parse(ac, av);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, win_width, win_height, "raycasting");
	img.img = mlx_new_image(data.mlx, win_width, win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = img;
	load_textures(&data);
	wall_textuers = malloc(sizeof(unsigned int) * win_width * win_height);
	player_inite(&player, data.mape->px, data.mape->py);
	data.player = player;
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	mlx_loop(data.mlx);
	return (0);
}
