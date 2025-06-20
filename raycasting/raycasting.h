/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/20 16:01:48 by aalahyan         ###   ########.fr       */
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
#define WALL_STRIP_W 1
#define FOV 60 * (M_PI /180)

#define RADIUS 5
#define ROTATION_SPEED 0.03
# include "all_data_struct.h"
# include "../minimap/minimap.h"
# include "../animation/animation.h"

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


int		key_press(int keycode, t_all_data *data);
int		key_release(int keycode, t_all_data *data);
int	handle_keys(void *param)
;
void	init_rays(t_rays *rays, int num_rays, double player_ang, int i);
void	player_inite(t_player *player, int x, int y, float angle);
double	distance_point(double x0, double y0, double x1, double y1);
double	normalize_angle(double angle);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		has_aw_wall(int x, int y, t_map *map);
void	clear_image(t_img *img);
double  get_x_offset(t_rays *ray);
t_img   *get_wall_texture(t_all_data *data, t_rays *ray);
void	horizontal_casting(t_rays *rays, t_player *player,t_map *map);
void	vertical_casting(t_rays *rays, t_player *player, t_map *map);
void    set_distance(t_rays *rays);
void	start_casting(t_player *player, t_img *img, t_map *map,t_all_data *data);
void	draw(t_all_data *data);
void	casting(t_rays *rays, t_player *player, t_map *map);
int     has_wall_with_radius(int px, int py, int radius, t_map *map);

#endif