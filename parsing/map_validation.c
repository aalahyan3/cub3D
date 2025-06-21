/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:54:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/21 14:19:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	element_validation(char **arr, int i, int j, int *n_players)
{
	if (!ft_strchr(" 01NEWS", arr[i][j]))
	{
		ft_putstr_fd("Error\nunsupported map token: ", 2);
		ft_putchar_fd(arr[i][j], 2);
		ft_putstr_fd(" in line :", 2);
		ft_putendl_fd(arr[i], 2);
		return (false);
	}
	if (ft_isalpha(arr[i][j]))
	{
		if ((arr[i][j + 1] && arr[i][j + 1] == ' ') \
		|| (j > 0 && arr[i][j - 1] == ' ') || (i > 0 && arr[i - 1][j] == ' ') \
		|| (arr[i + 1][j] && arr[i + 1][j] == ' '))
		{
			ft_putstr_fd("Error\nthe player must be inside the map.\n", 2);
			return (false);
		}
		*n_players += 1;
	}
	return (true);
}

bool	valid_elements(char **arr)
{
	int	i;
	int	j;
	int	n_players;

	1 && (i = 0, n_players = 0);
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!element_validation(arr, i, j, &n_players))
				return (false);
			j++;
		}
		i++;
	}
	if (n_players != 1)
	{
		ft_putendl_fd("Error\none \
player[N, E, S, W] must be present in map", 2);
		return (false);
	}
	return (true);
}

bool	map_has_newlines(char **map)
{
	int		i;
	bool	nl_found;

	nl_found = false;
	i = 0;
	while (map[i])
	{
		if (!*map[i])
			nl_found = true;
		if (*map[i] && nl_found)
			return (true);
		i++;
	}
	return (false);
}

bool	map_validation(char **map, t_map *map_s)
{
	if (!valid_elements(map))
		return (false);
	if (map_has_newlines(map))
	{
		ft_putstr_fd("Error\nthe map \
		rows must not be separated by newlines\n", 2);
		return (false);
	}
	adjust_map_structure(map);
	if (!surrounded_by_walls(map, map_s))
		return (false);
	return (true);
}
