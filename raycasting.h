/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:10 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/12 13:53:57 by zkhourba         ###   ########.fr       */
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
typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;
typedef struct s_player
{
	int	x;
	int	y;
	double pdx;
	double pdy;
	double pa;
}t_player;
typedef struct s_all_data
{
  	struct s_img img;
  	struct s_player player;
	void				*mlx;
	void				*mlx_win;
	int				map[10][10];
}t_all_data;



#endif