/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:46:49 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/19 13:58:49 by aalahyan         ###   ########.fr       */
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
	data->frames[0].img = mlx_xpm_file_to_image(data->mlx, "./textures/frame_1.xpm", &data->frames[0].width, &data->frames[0].height);
	data->frames[1].img = mlx_xpm_file_to_image(data->mlx, "./textures/frame_2.xpm", &data->frames[1].width, &data->frames[1].height);
	data->frames[2].img = mlx_xpm_file_to_image(data->mlx, "./textures/frame_3.xpm", &data->frames[2].width, &data->frames[2].height);
	data->frames[3].img = mlx_xpm_file_to_image(data->mlx, "./textures/frame_4.xpm", &data->frames[3].width, &data->frames[3].height);
	data->crosshair.img = mlx_xpm_file_to_image(data->mlx, "./textures/crosshair.xpm", &data->crosshair.width, &data->crosshair.width);
	if (!data->mape->n_texture.img || !data->mape->e_texture.img || !data->mape->s_texture.img || \
	!data->mape->w_texture.img || !data->frames[0].img || !data->frames[1].img || !data->frames[2].img || !data->frames[3].img)
	{
		ft_mlx_destroy_image(data->mlx, data->mape->n_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->s_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->e_texture.img);
		ft_mlx_destroy_image(data->mlx, data->mape->w_texture.img);
		ft_mlx_destroy_image(data->mlx, data->frames[0].img);
		ft_mlx_destroy_image(data->mlx, data->frames[1].img);
		ft_mlx_destroy_image(data->mlx, data->frames[2].img);
		ft_mlx_destroy_image(data->mlx, data->frames[3].img);
		ft_putstr_fd("Error\nerror while opening an image file.\n", 2);
		clear_map(data->mape);
		free(data->mlx);
		exit(1);
	}
	data->mape->n_texture.addr = mlx_get_data_addr(data->mape->n_texture.img,\
						&data->mape->n_texture.bits_per_pixel, &data->mape->n_texture.line_length, &data->mape->n_texture.endian);
	data->mape->s_texture.addr = mlx_get_data_addr(data->mape->s_texture.img,\
						&data->mape->s_texture.bits_per_pixel, &data->mape->s_texture.line_length, &data->mape->s_texture.endian);
	data->mape->w_texture.addr = mlx_get_data_addr(data->mape->w_texture.img,\
						&data->mape->w_texture.bits_per_pixel, &data->mape->w_texture.line_length, &data->mape->w_texture.endian);
	data->mape->e_texture.addr = mlx_get_data_addr(data->mape->e_texture.img,\
						&data->mape->e_texture.bits_per_pixel, &data->mape->e_texture.line_length, &data->mape->e_texture.endian);
	data->frames[0].addr = mlx_get_data_addr(data->frames[0].img, &data->frames[0].bits_per_pixel, &data->frames[0].line_length, &data->frames[0].endian);
	data->frames[1].addr = mlx_get_data_addr(data->frames[1].img, &data->frames[1].bits_per_pixel, &data->frames[1].line_length, &data->frames[1].endian);
	data->frames[2].addr = mlx_get_data_addr(data->frames[2].img, &data->frames[2].bits_per_pixel, &data->frames[2].line_length, &data->frames[2].endian);
	data->frames[3].addr = mlx_get_data_addr(data->frames[3].img, &data->frames[3].bits_per_pixel, &data->frames[3].line_length, &data->frames[3].endian);
}