/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:04:44 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/14 16:38:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

bool    valid_extension(char *filename)
{
    char *ext;

    ext = ft_strrchr(filename, '.');
    if (!ext)
        return (false);
    return (ft_strncmp(ext, ".cub", 5) == 0);
}
static void print_error(char *err)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    ft_putendl_fd(err, STDERR_FILENO);
    exit(1);
}

t_map   *parse(int ac, char **av)
{
    int     fd;
    t_map   *map;

    if (ac != 2)
        print_error(NO_ARG);
    else if (!valid_extension(av[1]))
        print_error(INV_EXT);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        print_error(strerror(errno));
    map = malloc(sizeof(t_map));
    if (!map)
    {
        close(fd);
        print_error("malloc");
    }
    fill_map_data(map, fd);
    return (map);
}
