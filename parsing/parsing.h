/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:53:43 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "../libft/libft.h"

# define NO_ARG "Invalid argument - usage: ./cub3d *.cub."
# define INV_EXT "Invalid extension - *.cub is required."

# define COUNTER_INDEX 0
# define CIEL_INDEX 1
# define FLOOR_INDEX 2

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_map
{
	char	**arr;
	int		ceil_color;
	int		floor_color;
	int		map_w;
	int		map_h;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	t_img	n_texture;
	t_img	s_texture;
	t_img	e_texture;
	t_img	w_texture;
	int		px;
	int		py;
	float	i_angle;
}	t_map;

t_map	*parse(int ac, char **av);
void	clear_map(t_map *map);
void	fill_map_data(t_map *map, int fd);
void	free_2d_array(char **arr);
bool	map_validation(char **map, t_map *map_s);
void	start_map_reading(t_map *map, char *line, int fd);
bool	set_attribute(t_map *map, char *line, int *infos);
void	exit_error(t_map *map, char *line, int fd);
char	*path_skipper(char *path);
void	adjust_map_structure(char **map);
bool	surrounded_by_walls(char **map, t_map *map_s);
int		atoi_for_rgb(char *s, char *line);

#endif