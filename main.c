/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/16 10:49:52 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	draw(t_all_data *data)
{
	clear_image(&data->img);
	start_casting(&data->player, &data->img, data->map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}


int main(int ac, char **av)
{
	t_img img;
	t_player player;
	t_all_data data;

	data.mape = parse(ac, av);
	int map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	data.mlx = mlx_init();
	load_textures(&data);
	data.mlx_win = mlx_new_window(data.mlx, 10 * TAIL, 10 * TAIL, "raycasting");
	img.img = mlx_new_image(data.mlx, 10 * TAIL, 10 * TAIL);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = img;
	player_inite(&player);
	data.player = player;
	memcpy(data.map, map, sizeof(map));
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	mlx_loop(data.mlx);
	return (0);
}
