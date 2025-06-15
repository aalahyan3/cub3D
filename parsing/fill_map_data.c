/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:37:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/14 22:01:32 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void init_map(t_map *map, int *helper_infos)
{
	map->arr = NULL;
	map->e_path = NULL;
	map->n_path = NULL;
	map->s_path = NULL;
	map->w_path = NULL;
	ft_bzero(helper_infos, 3 * sizeof(int));
}
void exit_error(t_map *map, char *line, int fd)
{
	close(fd);
	clear_map(map);
	free(line);
	exit(1);
}

bool    parse_path(char *path, char *ptr)
{
	int		i;
	bool	error;

	error = false;
	if  (ptr != NULL)
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

char    *path_skipper(char *path)
{
	while (*path && *path != ' ')
		path++;
	while (*path && *path == ' ')
		path++;
	return (path);
}

bool parse_color(char *color, int state)
{
	int i;
	int	colors;
	bool	error;

	i = 0;
	error = false;
	if (state)
	{
		ft_putendl_fd("Error\nColor attribute duplicate was found.", 2);
		return (false);
	}
	while (color[i] && color[i] != ' ')
		i++;
	while (color[i] && color[i] == ' ')
		i++;
	colors  = 0;
	while (color[i] && !error && color[i] != '\n')
	{
		if (color[i] == ',')
			colors++;
		else if (!ft_isdigit(color[i]))
			error = true;
		i++;
	}
	if (error || colors != 2)
	{
		ft_putstr_fd("Error\nParse error in line: ", 2);
		ft_putendl_fd(color, 2);
		return (false);
	}
	return (true);
}

int	get_color_from_rgb(char *line)
{
	int rgb[3];
	char	**arr;

	while (*line && !ft_isdigit(*line))
		line++;
	arr = ft_split(line, ',');
	if (!arr)
		return (-1);
	rgb[0] = ft_atoi(arr[0]);
	rgb[1] = ft_atoi(arr[1]);
	rgb[2] = ft_atoi(arr[2]);
	// free the array later
	return ((rgb[0] << 16 | (rgb[1] << 8) | (rgb[2])));
}

bool    set_attribute(t_map *map, char *line, int *infos)
{
	if (*line == 'N')
	{
		if (!parse_path(line, map->n_path))
			return (false);
		map->n_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (*line == 'S')
	{
		if (!parse_path(line, map->s_path))
			return (false);
		map->s_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (*line == 'W')
	{
		if (!parse_path(line, map->w_path))
			return (false);
		map->w_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (*line == 'E')
	{
		if (!parse_path(line, map->e_path))
			return (false);
		map->e_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (*line == 'C')
	{
		if (!parse_color(line, infos[CIEL_INDEX]))
			return (false);
		infos[CIEL_INDEX] = 1;
		map->seil_color = get_color_from_rgb(line);
		ft_printf("color is %d\n", map->seil_color);
		return (true);
	}
	return (false);
}

void    fill_map_data(t_map *map, int fd)
{
	char    *line;
	int     helper_infos[3]; // [nb_attr_seen, i have ciel, i have floor] default [0, 0 , 0]

	init_map(map, helper_infos);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '0' && *line != '1' && *line != ' ' && *line != '\n')
		{
			if (!set_attribute(map, line, helper_infos))
				exit_error(map, line, fd);
		}
		free(line);
		line = get_next_line(fd);
	}
}