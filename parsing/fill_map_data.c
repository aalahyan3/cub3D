/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:37:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/15 21:28:14 by aalahyan         ###   ########.fr       */
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
		ft_putstr_fd(color, 2);
		return (false);
	}
	return (true);
}

int	atoi_for_rgb(char *s, char *line)
{
	int res;
	int	i;
	int	digits;

	res = 0;
	i = 0;
	if (! s || !*s)
	{
		ft_putstr_fd("Error\nnon valid rgb value in : ", 2);
		ft_putstr_fd(line, 2);
		return (-1);
	}
	digits = 0;
	while (s[i] && s[i] == '0')
		i++;
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		i++;
		digits++;
	}
	if (digits > 3 || res > 255)
	{
		ft_putstr_fd("Error\nnon valid rgb value in : ", 2);
		ft_putstr_fd(line, 2);
		return (-1);
	}
	return (res);
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
	rgb[0] = atoi_for_rgb(arr[0], line);
	rgb[1] = atoi_for_rgb(arr[1], line);
	rgb[2] = atoi_for_rgb(arr[2], line);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	// free the array later
	return ((rgb[0] << 16 | (rgb[1] << 8) | (rgb[2])));
}

bool    set_attribute(t_map *map, char *line, int *infos)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (!parse_path(line, map->n_path))
			return (false);
		map->n_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (!parse_path(line, map->s_path))
			return (false);
		map->s_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (!parse_path(line, map->w_path))
			return (false);
		map->w_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (!parse_path(line, map->e_path))
			return (false);
		map->e_path = ft_strdup(path_skipper(line));
		return (true);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (!parse_color(line, infos[CIEL_INDEX]))
			return (false);
		infos[CIEL_INDEX] = 1;
		map->ceil_color = get_color_from_rgb(line);
		return (map->ceil_color >= 0);
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		if (!parse_color(line, infos[FLOOR_INDEX]))
			return (false);
		infos[FLOOR_INDEX] = 1;
		map->floor_color = get_color_from_rgb(line);
		return (map->floor_color >= 0);
	}
	else
	{
		ft_putstr_fd("Error\nunknown symbol in line: ", 2);
		ft_putstr_fd(line, 2);
		return (false);
	}
}

int get_sizeof_map(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

bool	add_line_to_map(t_map *map, char *line)
{
	char	**new;
	int		size;
	int		i;

	size = get_sizeof_map(map->arr) + 2;
	new = malloc(sizeof(char *) * size);
	if (!new)
		return (false);
	i = 0;
	while (map->arr && map->arr[i])
	{
		new[i] = ft_strdup(map->arr[i]);
		i++;
	}
	new[i++] = ft_strtrim(line, "\n");
	new[i] = NULL;
	free_2d_array(map->arr);
	map->arr = new;
	return (true);
}

void	start_map_reading(t_map *map, char *line, int fd)
{
	while (line)
	{
		if (!add_line_to_map(map, line))
		{
			exit_error(map, line, fd);
		}
		free(line);
		line = get_next_line(fd);
	}
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
			helper_infos[0] += 1;
		}
		else if (*line == '1' || *line == ' ' || *line == '0')
		{
			if (helper_infos[0] != 6)
			{
				ft_putstr_fd("Error\nthe map was found before all data provided.\n", 2);
				exit_error(map, line, fd);
			}
			start_map_reading(map, line, fd);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
}