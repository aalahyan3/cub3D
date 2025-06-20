/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:24:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 17:32:01 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_sizeof_map(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
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
