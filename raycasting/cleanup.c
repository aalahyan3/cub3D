/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:52:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 17:00:56 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void destroy_textures(t_all_data *data)
{
	mlx_destroy_image(data->mlx, data->mape->e_texture.img);
	mlx_destroy_image(data->mlx, data->mape->n_texture.img);
	mlx_destroy_image(data->mlx, data->mape->s_texture.img);
	mlx_destroy_image(data->mlx, data->mape->w_texture.img);
	mlx_destroy_image(data->mlx, data->frames[0].img);
	mlx_destroy_image(data->mlx, data->frames[1].img);
	mlx_destroy_image(data->mlx, data->frames[2].img);
	mlx_destroy_image(data->mlx, data->frames[3].img);
	mlx_destroy_image(data->mlx, data->crosshair.img);
}

void	cleanup(t_all_data *data)
{
	destroy_textures(data);
	clear_map(data->mape);
	free(data->mlx);
	exit(1);
}