/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:26:31 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/21 14:21:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_path(char *path, char *ptr)
{
	int		i;
	bool	error;

	error = false;
	if (ptr != NULL)
	{
		ft_putendl_fd("Error\nTexture path duplicate was found.", 2);
		return (false);
	}
	i = 0;
	while (path[i] && path[i] != ' ')
		i++;
	if (!path[i])
		error = true;
	while (path[i] && path[i] == ' ')
		i++;
	if (!path[i] || error)
	{
		ft_putstr_fd("Error\nParse error at line: ", 2);
		ft_putendl_fd(path, 2);
		return (false);
	}
	return (true);
}

bool	parse_color(char *color, int state)
{
	int		i;
	int		colors;
	bool	error;

	1 && (i = 0, error = false, colors = 0);
	if (state)
		return (ft_putendl_fd("Error\nColor \
attribute duplicate was found.", 2), false);
	while (color[i] && color[i] != ' ')
		i++;
	while (color[i] && color[i] == ' ')
		i++;
	while (color[i] && !error && color[i] != '\n')
	{
		if (color[i] == ',')
			colors++;
		else if (!ft_isdigit(color[i]))
			error = true;
		i++;
	}
	if (error || colors != 2)
		return (ft_putstr_fd("Error\nParse error in line: ", 2), \
		ft_putstr_fd(color, 2), false);
	return (true);
}

int	get_color_from_rgb(char *line)
{
	int		rgb[3];
	char	**arr;

	while (*line && !ft_isdigit(*line))
		line++;
	arr = ft_split(line, ',');
	if (!arr)
		return (-1);
	rgb[0] = atoi_for_rgb(arr[0], line);
	rgb[1] = atoi_for_rgb(arr[1], line);
	rgb[2] = atoi_for_rgb(arr[2], line);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	free_2d_array(arr);
	return ((rgb[0] << 16 | (rgb[1] << 8) | (rgb[2])));
}

bool	set_attribute_2(t_map	*map, char *line, int *infos)
{
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (!parse_path(line, map->e_path))
			return (false);
		return (map->e_path = ft_strtrim(path_skipper(line), " \n"), true);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (!parse_color(line, infos[CIEL_INDEX]))
			return (false);
		return (infos[CIEL_INDEX] = 1, \
map->ceil_color = get_color_from_rgb(line), map->ceil_color >= 0);
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		if (!parse_color(line, infos[FLOOR_INDEX]))
			return (false);
		return (infos[FLOOR_INDEX] = 1, \
		map->floor_color = get_color_from_rgb(line), map->floor_color >= 0);
	}
	else
		return (ft_putstr_fd("Error\nunknown symbol in line: ", 2), \
		ft_putstr_fd(line, 2), false);
}

bool	set_attribute(t_map *map, char *line, int *infos)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (!parse_path(line, map->n_path))
			return (false);
		map->n_path = ft_strtrim(path_skipper(line), " \n");
		return (true);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (!parse_path(line, map->s_path))
			return (false);
		map->s_path = ft_strtrim(path_skipper(line), " \n");
		return (true);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (!parse_path(line, map->w_path))
			return (false);
		map->w_path = ft_strtrim(path_skipper(line), " \n");
		return (true);
	}
	return (set_attribute_2(map, line, infos));
}
