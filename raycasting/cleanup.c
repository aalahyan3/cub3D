/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:52:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/21 15:00:06 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void destroy_textures(t_all_data *data)
{
	mlx_destroy_image(data->mlx, data->map->e_texture.img);
	mlx_destroy_image(data->mlx, data->map->n_texture.img);
	mlx_destroy_image(data->mlx, data->map->s_texture.img);
	mlx_destroy_image(data->mlx, data->map->w_texture.img);
	mlx_destroy_image(data->mlx, data->frames[0].img);
	mlx_destroy_image(data->mlx, data->frames[1].img);
	mlx_destroy_image(data->mlx, data->frames[2].img);
	mlx_destroy_image(data->mlx, data->frames[3].img);
	mlx_destroy_image(data->mlx, data->crosshair.img);
}

void	cleanup(t_all_data *data, int status)
{
	destroy_textures(data);
	clear_map(data->map);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	free(data->mlx);
	exit(status);
}