/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_data_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:50:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/22 15:20:28 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_DATA_STRUCT_H
# define ALL_DATA_STRUCT_H

# include "../parsing/parsing.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define TILE_SIZE 80
# define RADIUS 5

typedef struct s_rays
{
	double	ray_angl;
	double	ver_distance;
	double	hori_distance;
	double	wall_hit_x_h;
	double	wall_hit_y_h;
	double	wall_hit_x_v;
	double	wall_hit_y_v;
	double	wall_hit_x;
	double	wall_hit_y;
	double	rays_dis;
	int		coulumn;
	short	up;
	short	down;
	short	left;
	short	right;
	short	found_hori;
	short	found_ver;
}	t_rays;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	space;
	int	up;
	int	down;
}	t_keys;

typedef struct s_maping_tex
{
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	double	x_offset;
	int		w;
	int		draw_x;

}	t_maping_tex;
typedef struct s_player
{
	double	x;
	double	y;
	double	pa;
	double	pdx;
	double	pdy;
	double	speed;
	int		num_rays;
	int		shot;
}	t_player;

typedef struct s_all_data
{
	t_img			img;
	t_keys			keys;
	t_player		player;
	t_img			frames[4];
	t_img			crosshair;
	void			*mlx;
	void			*mlx_win;
	t_map			*map;
	t_rays			*rays;
	int				cursor_x;
	int				cursor_y;
	int				minimap_scale;
	t_maping_tex	tex_data;
}	t_all_data;

#endif