/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:06:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/09/21 16:34:34 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] != 'b' || str[i - 2] != 'u'
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (0);
	return (1);
}

int	detect_isline_map(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '1' || str[i] == '0' || str[i] == ' ')
		return (1);
	return (0);
}

char	*new_updated_line(t_gc *gc, int size, char *line)
{
	char	*new_line;
	int		i;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_line = gc_malloc(gc, size);
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < size - 1)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*new_paths_line(t_gc *gc, char *line)
{
	char	*new_line;
	int		i;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_line = gc_malloc(gc, ft_strlen(line) + 1);
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	count_nbr_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
