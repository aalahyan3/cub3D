/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 16:06:59 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	draw_floor_and_ceiling(void *img, int ceiling_color, int floor_color)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
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
	data.mape = parse(ac, av);
	data.mlx = mlx_init();
	data.cursor_x =-1 ;
	data.cursor_y = 0;
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "raycasting");
	img.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = img;
	load_textures(&data);
	player_inite(&player, data.mape->px, data.mape->py, data.mape->i_angle);
	data.player = player;
	data.keys.a = 0;
	data.keys.s = 0;
	data.keys.w = 0;
	data.keys.d = 0;
	data.is_door = 0;
	data.keys.left = 0;
	data.keys.right = 0;
	data.keys.space = 0;
	data.minimap_scale = 10;
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx_win, 6, 1 << 6, mouse_handler, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	mlx_loop(data.mlx);
	return (0);
}
