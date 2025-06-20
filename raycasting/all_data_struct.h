/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_data_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:50:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 17:09:11 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_DATA_STRUCT_H
# define ALL_DATA_STRUCT_H

# include "../parsing/parsing.h"
#define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define TILE_SIZE 80
#define RADIUS 5
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
	double  rays_dis;
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
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
    int space;
    int up;
    int down;
}	t_keys;

// typedef struct s_texture {
//     void    *img;           // MLX image pointer
//     char    *data;          // raw pixel data
//     int     width;
//     int     height;
//     int     bpp;
//     int     line_len;
//     int     endian;
// }   t_texture;
typedef struct s_maping_tex
{
    t_img *tex;
	int tex_x;
    int tex_y;
	double x_offset;
	int w; 
    int draw_x;
    
}t_maping_tex;
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
    t_map       *map;
    t_rays      *rays;
    int cursor_x;
    int cursor_y;
    int minimap_scale;
    t_maping_tex tex_data;
}   t_all_data;

#endif