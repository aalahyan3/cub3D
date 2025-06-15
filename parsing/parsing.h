/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:53:43 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/15 14:55:07 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include <stdbool.h>
#include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

# define NO_ARG "Invalid argument - usage: ./cub3d *.cub."
# define INV_EXT "Invalid extension - *.cub is required."

# define COUNTER_INDEX 0
# define CIEL_INDEX 1
# define FLOOR_INDEX 2

typedef struct s_map
{
    char    **arr;
    int     ceil_color;
    int     floor_color;
    char    *n_path;
    char    *s_path;
    char    *w_path;
    char    *e_path;
}   t_map;

t_map   *parse(int ac, char **av);
void clear_map(t_map *map);
void    fill_map_data(t_map *map, int fd);
void free_2d_array(char **arr);
bool	map_validation(char **map);

#endif