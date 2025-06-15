/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:54:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/15 16:59:09 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	valid_elements(char **arr)
{
	int	i;
	int	j;
	int	n_players;

	i = 0;
	n_players = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] != ' ' && arr[i][j] != '0' && arr[i][j] != '1' && arr[i][j] != 'N' && arr[i][j] != 'S' && arr[i][j] != 'W' && arr[i][j] != 'E')
			{
				ft_putstr_fd("Error\nunsupported map token: ", 2);
				ft_putchar_fd(arr[i][j], 2);
				ft_putstr_fd(" in line :", 2);
				ft_putendl_fd(arr[i], 2);
				return (false);
			}
			if (ft_isalpha(arr[i][j]))
				n_players++;
			j++;;
		}
		i++;
	}
	if (n_players != 1)
	{
		ft_putendl_fd("Error\nmore than one player position present in the map", 2);
		return (false);
	}
	return (true);
}

bool	surrounded_by_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || j == 0 || !map[i+1] || !map[i][j+1])
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
				{
					ft_putstr_fd("Error\nthe map must be surrounded by wall\n", 2);
					return (false);
				}
			}
			if (map[i][j] == ' ')
			{
				if ((map[i][j + 1] && (map[i][j + 1] != '1' && map[i][j + 1] != ' ' )) || (j!=0 && (map[i][j - 1] != '1' && map[i][j - 1] != ' ')) || (map[i+1] && (map[i+1][j] != '1' && map[i+1][j] != ' ')) || (i!=0 && (map[i-1][j] != '1' && map[i - 1][j] != ' ')))
				{
					ft_putstr_fd("Error\nthe map must be surrounded by wall\n", 2);
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}


bool map_has_newlines(char **map)
{
	int	i;
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
bool	map_validation(char **map)
{
	if (!valid_elements(map))
		return (false);
	if (map_has_newlines(map))
	{
		ft_putstr_fd("Error\nthe map rows must not be separated by newlines\n", 2);
		return (false);
	}
	if (!surrounded_by_walls(map))
		return (false);
	return (true);
}