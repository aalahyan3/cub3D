/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/18 16:07:42 by aalahyan         ###   ########.fr       */
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

# include "../parsing/parsing.h"
# include "all_data_struct.h"
# include "../minimap/minimap.h"
#define wall_strip 1
#define FOV 60     * (M_PI /180)
#define TAIL 80
#define win_width 800
#define win_height 800
#define RADUIS 5
# define ROTATION_SPEED 0.03
typedef struct s_proj
{
    double corr_dist;
    double strip_h;
    double draw_s;
    double draw_e;
}	t_proj;


 typedef struct s_wall
{
    int    x;
    int    width;
    double y_start;
    double y_end;
    int    color;
    t_img *img;
}	t_wall;

typedef struct s_vcast
{
    double xint;
    double yint;
    double xstep;
    double ystep;
    double nx;
    double ny;
}               t_vcast;
typedef struct s_cast
{
    double xint;
    double yint;
    double xstep;
    double ystep;
    double nx;
    double ny;
}               t_cast;
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


#define TEX_NORTH 0
#define TEX_SOUTH 1
#define TEX_EAST  2
#define TEX_WEST  3

// Texture structure



int		key_press(int keycode, t_all_data *data);
int		key_release(int keycode, t_all_data *data);
int		handle_keys(t_all_data *d);
void	init_rays(t_rays *rays, int num_rays, double player_ang, int i);
void	player_inite(t_player *player, int x, int y, float angle);
double	distance_point(double x0, double y0, double x1, double y1);
double	normalize_angle(double angle);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		has_aw_wall(int x, int y, t_map *map);
void	clear_image(t_img *img);
void	horizontal_casting(t_rays *rays, t_player *player,t_map *map);
void	vertical_casting(t_rays *rays, t_player *player, t_map *map);
void	start_casting(t_player *player, t_img *img, t_map *map,t_all_data *data);
void	draw(t_all_data *data);
void	casting(t_rays *rays, t_player *player, t_map *map);
void draw_wall_column(t_all_data *data, t_rays *r, int x);
int has_wall_with_radius(int px, int py, int radius, t_map *map);

#endif