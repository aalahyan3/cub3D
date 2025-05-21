/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:10 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/20 14:50:39 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define wall_strip 1
#define FOV 60 * (M_PI /180)
#define TAIL 64
#define win_width 640
#define win_hight 640
#define win_map_w 640
#define win_map_h 640
#define BUFFER_SIZE (img->line_length * win_hight)

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;
typedef struct  s_player {
    double  x, y;
    double  pa;
    double  pdx, pdy;
    double  speed;
    int     num_rays;
}               t_player;
 
 typedef struct s_rays
{
	double ray_angl;
	double ver_distance;
	double	hori_distance;
	double	Wall_hit_x_h;
	double	Wall_hit_y_h;
	double	Wall_hit_x_v;
	double	Wall_hit_y_v;
	double	Wall_hit_x;
	double	Wall_hit_y;
	double rays_dis;
	int		coulumn;
	short	up;
	short	down;
	short	left;
	short	right;
	short	found_hori;
	short	found_ver;
}t_rays;
 
 typedef struct s_keys
{
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_all_data
{
  	struct s_img img;
	t_keys	keys;
  	struct s_player player;
	void				*mlx;
	void				*mlx_win;
	int				map[10][10];
	
}t_all_data;

#endif