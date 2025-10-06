/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:12:04 by aykassim          #+#    #+#             */
/*   Updated: 2025/09/23 11:27:59 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_typed_good(char *color)
{
	int	i;
	int	cm;

	cm = 0;
	i = 0;
	if (color[0] == ',' || color[ft_strlen(color) - 1] == ',')
		return (0);
	while (color[i])
	{
		if (color[i] == ',')
			cm++;
		i++;
	}
	if (cm != 2)
		return (0);
	while (color[i])
	{
		if (color[i] != ',' && !ft_isdigit(color[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_color(t_gc *gc, char *color)
{
	char	**res;
	int		i;

	if (!is_typed_good(color))
		return (0);
	res = ft_split(gc, color, ',');
	if (count_nbr_line(res) != 3)
		return (0);
	i = 0;
	while (res[i])
	{
		if (ft_strlen(res[i]) > 3)
			return (0);
		i++;
	}
	i = 0;
	while (res[i])
	{
		if (ft_atoi(res[i]) > 255 || ft_atoi(res[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	validat_line(t_game **game, char *line)
{
	int	i;

	(*game)->m_height++;
	if ((*game)->m_width < (int)ft_strlen(line))
		(*game)->m_width = ft_strlen(line);
	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			(*game)->is_player++;
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_first_args(t_game **game, char *str, char *str1)
{
	if (ft_strcmp(str, "NO") == 0 && !(*game)->no_path)
		(*game)->no_path = ft_strdup((*game)->gc, str1);
	else if (ft_strcmp(str, "SO") == 0 && !(*game)->so_path)
		(*game)->so_path = ft_strdup((*game)->gc, str1);
	else if (ft_strcmp(str, "WE") == 0 && !(*game)->we_path)
		(*game)->we_path = ft_strdup((*game)->gc, str1);
	else if (ft_strcmp(str, "EA") == 0 && !(*game)->ea_path)
		(*game)->ea_path = ft_strdup((*game)->gc, str1);
	else if (ft_strcmp(str, "C") == 0 && !(*game)->c_color)
	{
		if (!validate_color((*game)->gc, str1))
			return (0);
		(*game)->c_color = ft_strdup((*game)->gc, str1);
	}
	else if (ft_strcmp(str, "F") == 0 && !(*game)->f_color)
	{
		if (!validate_color((*game)->gc, str1))
			return (0);
		(*game)->f_color = ft_strdup((*game)->gc, str1);
	}
	else
		return (0);
	return (1);
}

int	convert_color_to_rgb(t_game **game)
{
	char	**f_colors;
	char	**c_colors;
	int		r_color;
	int		g_color;
	int		b_color;

	f_colors = ft_split((*game)->gc, (*game)->f_color, ',');
	if (!f_colors)
		return (0);
	r_color = ft_atoi(f_colors[0]);
	g_color = ft_atoi(f_colors[1]);
	b_color = ft_atoi(f_colors[2]);
	(*game)->floor_color = (r_color << 24) | (g_color << 16) | (b_color << 8) | 255;
	c_colors = ft_split((*game)->gc, (*game)->c_color, ',');
	if (!c_colors)
		return (0);
	r_color = ft_atoi(c_colors[0]);
	g_color = ft_atoi(c_colors[1]);
	b_color = ft_atoi(c_colors[2]);
	(*game)->ceil_color = (r_color << 24) | (g_color << 16) | (b_color << 8) | 255;
	return (1);
}

int	validate_path(t_game **game)
{
	char	**res;
	int		i;

	i = 0;
	while ((*game)->paths[i])
	{
		res = ft_split((*game)->gc, (*game)->paths[i], ' ');
		if (count_nbr_line(res) != 2)
			return (0);
		if (!check_first_args(game, res[0], res[1]))
			return (0);
		i++;
	}
	return (1);
}
