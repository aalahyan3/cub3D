/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:54:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/16 20:53:44 by aalahyan         ###   ########.fr       */
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
			{
				n_players++;
				if ((arr[i][j + 1] && arr[i][j + 1] == ' ') || (j > 0 && arr[i][j - 1] == ' ') || (i > 0 && arr[i - 1][j] == ' ') || (arr[i + 1][j] && arr[i + 1][j] == ' '))
				{
					ft_putstr_fd("Error\nthe player must be inside the map.\n", 2);
					return (false);
				}
			}
			j++;;
		}
		i++;
	}
	if (n_players != 1)
	{
		ft_putendl_fd("Error\none player[N, E, S, W] must be present in map", 2);
		return (false);
	}
	return (true);
}

bool	surrounded_by_walls(char **map, t_map *map_s)
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
					ft_putstr_fd("Error\nthe map must be surrounded by wall1\n", 2);
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
			if (ft_isalpha(map[i][j]))
			{
				map_s->px = j;
				map_s->py = i;
				if (map[i][j] == 'N')
					map_s->i_angle = M_PI_2;
				else if (map[i][j] == 'S')
					map_s->i_angle = 3 * M_PI_2;
				else if (map[i][j] == 'W')
					map_s->i_angle = M_PI;
				else if (map[i][j] == 'E')
					map_s->i_angle = 0.0;
			}
			j++;
		}
		i++;
	}
	map_s->map_w = j;
	map_s->map_h = i;
	ft_printf("initial %d %d\n", i, j);
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
int	get_longest_row(char **map)
{
	int	longest;
	int	i;

	i = 0;
	longest = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	return (longest);
}

void adjust_map_structure(char **map)
{
	int	longest;
	int	i;
	char	*new;
	int		j;

	longest = get_longest_row(map);
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < longest)
		{
			new = malloc(sizeof(char) * (longest + 1));
			if (!new)
				return ;
			j = 0;
			while (j < ft_strlen(map[i]))
			{
				new[j] = map[i][j];
				j++;
			}
			while (j < longest)
				new[j++] = ' ';
			new[j] = 0;
			free(map[i]);
			map[i] = new;
		}
		i++;
	}
}

bool	map_validation(char **map, t_map *map_s)
{
	if (!valid_elements(map))
		return (false);
	if (map_has_newlines(map))
	{
		ft_putstr_fd("Error\nthe map rows must not be separated by newlines\n", 2);
		return (false);
	}
	adjust_map_structure(map);
	// for (int i = 0 ; map[i]; i++)
	// 	ft_printf("%s\n", map[i]);
	if (!surrounded_by_walls(map, map_s))
		return (false);
	return (true);
}