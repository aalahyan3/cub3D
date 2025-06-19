/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_data_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:50:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/19 14:10:18 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_DATA_STRUCT_H
# define ALL_DATA_STRUCT_H

# include "../parsing/parsing.h"

#define NUM_TEXTURES 4

 typedef struct s_keys
{
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
    int space;
}	t_keys;

typedef struct s_texture {
    void    *img;           // MLX image pointer
    char    *data;          // raw pixel data
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

typedef struct  s_player {
    double  x, y;
    double  pa;
    double  pdx, pdy;
    double  speed;
    int     num_rays;
    int     shot;
}	t_player;

typedef struct s_all_data
{
    t_img       img;
    t_keys      keys;
    t_player    player;
    t_img       frames[4];
    t_img       crosshair;
    void        *mlx;
    void        *mlx_win;
    t_map       *mape;
    int         map[10][10];
    t_texture   textures[NUM_TEXTURES];
    int cursor_x;
    int cursor_y;
}   t_all_data;

#endif