/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/22 14:03:56 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	cross_button(void *param)
{
	t_all_data	*d;

	d = (t_all_data *)param;
	cleanup(d, 0);
	return (0);
}

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

void	draw(t_all_data *data)
{
	clear_image(&data->img);
	draw_floor_and_ceiling(&data->img, \
	data->map->ceil_color, data->map->floor_color);
	start_casting(&data->player, &data->img, data->map, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

void	init_data(t_all_data *data, int ac, char **av)
{
	t_player	player;
	t_img		image;

	ft_memset(data, 0, sizeof(t_all_data));
	1 && (data->map = parse(ac, av), data->mlx = mlx_init());
	if (!data->mlx)
	{
		clear_map(data->map);
		exit(1);
	}
	load_textures(data);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->mlx_win)
		cleanup(data, 1);
	image.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!image.img)
		cleanup(data, 1);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, \
	&image.line_length, &image.endian);
	if (!image.addr)
		cleanup(data, 1);
	player_inite(&player, data->map->px, data->map->py, data->map->i_angle);
	data->player = player;
	ft_bzero(&data->keys, sizeof(t_keys));
	1 && (data->img = image, data->minimap_scale = 5, data->cursor_x = -1);
}

int	main(int ac, char **av)
{
	t_all_data	data;

	init_data(&data, ac, av);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx_win, 6, 1 << 6, mouse_handler, &data);
	mlx_hook(data.mlx_win, 17, 0, cross_button, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	mlx_loop(data.mlx);
	return (0);
}
