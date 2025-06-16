/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:46:49 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/16 10:47:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_destroy_image(void *mlx, void *img)
{
	if (!img)
		return ;
	mlx_destroy_image(mlx, img);
}
void	load_textures(t_all_data *data)
{
	data->mape->n_texture.img = mlx_xpm_file_to_image(data->mlx, data->mape->n_path, &data->mape->n_texture.width, &data->mape->n_texture.height);
	data->mape->s_texture.img = mlx_xpm_file_to_image(data->mlx, data->mape->s_path, &data->mape->s_texture.width, &data->mape->s_texture.height);
	data->mape->w_texture.img = mlx_xpm_file_to_image(data->mlx, data->mape->w_path, &data->mape->w_texture.width, &data->mape->w_texture.height);
	data->mape->e_texture.img = mlx_xpm_file_to_image(data->mlx, data->mape->e_path, &data->mape->e_texture.width, &data->mape->e_texture.height);
	if (!data->mape->n_texture.img || !data->mape->e_texture.img || !data->mape->s_texture.img || !data->mape->w_texture.img)
	{
		ft_mlx_destroy_image(data->mlx, data->mape->n_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->s_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->e_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->w_texture.img);
		ft_putstr_fd("Error\nerror while opening an image file.\n", 2);
		clear_map(data->mape);
		free(data->mlx);
		exit(1);
	}
}