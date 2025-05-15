/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:10 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/15 20:31:41 by zkhourba         ###   ########.fr       */
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
#define TAIL 32
#define win_width 320
#define win_hight 320
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
	double	Wall_hit_x;
	double	Wall_hit_y;
	int		coulumn;
	short	up;
	short	down;
	short	left;
	short	right;
	short	found;
}t_rays;
 
typedef struct s_all_data
{
  	struct s_img img;
  	struct s_player player;
	void				*mlx;
	void				*mlx_win;
	int				map[10][10];
	
}t_all_data;

#endif