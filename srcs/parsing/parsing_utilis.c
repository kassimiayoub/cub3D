/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/10/18 13:27:49 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	assis_func(t_game **game, t_fill_map **tf)
{
	close((*tf)->fd);
	if ((*tf)->j != 6 || (*tf)->j == 0 || (*tf)->cm == 0)
		return (0);
	(*game)->map[(*tf)->i] = NULL;
	(*game)->paths[(*tf)->j] = NULL;
	return (1);
}

int	fill_map_content(t_game **game, char *map)
{
	t_fill_map	*tf;

	initial_fillmap(game, map, &tf);
	tf->line = get_next_line((*game)->gc, tf->fd);
	while (tf->line)
	{
		if (detect_isline_map(tf->line))
		{
			if (!add_line_map(game, tf->line, &tf->cm, &tf->i))
				return (close(tf->fd), 0);
		}
		else
		{
			if (add_line_path(game, tf->line, tf->j) == 2)
			{
				tf->line = get_next_line((*game)->gc, tf->fd);
				continue ;
			}
			else if (add_line_path(game, tf->line, tf->j) == 0)
				return (close(tf->fd), 0);
			tf->j++;
		}
		tf->line = get_next_line((*game)->gc, tf->fd);
	}
	return (assis_func(game, &tf));
}

int	all_validate_element(t_game *game, char *map)
{
	if (game->is_player != 1)
		return (printf("Error:\n More than one player!!"), 0);
	if (!fill_map_content(&game, map))
		return (printf("Error:\n Map caracters invalid!!\n"), 0);
	if (!detect_map_is_valid(game))
		return (printf("Error:\n Map walls invalid!!\n"), 0);
	if (!validate_path(&game))
		return (printf("Error:\n  The path not there!!\n"), 0);
	if (!convert_color_to_rgb(&game))
		return (printf("Error:\n The colors Problem!!\n"), 0);
	if (!check_all_pathimg(game))
		return (printf("Error:\n The images path not valid\n"), 0);
	return (1);
}

int	read_map(t_game **game, char *map)
{
	int		fd;
	char	*line;
	int		flag;

	flag = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("Error:\n open map!!\n"), 0);
	line = get_next_line((*game)->gc, fd);
	while (line)
	{
		if (detect_isline_map(line))
			flag = 1;
		if (flag)
		{
			if (!validat_line(game, line))
				return (close(fd), 0);
		}
		line = get_next_line((*game)->gc, fd);
	}
	close(fd);
	if (!all_validate_element(*game, map))
		return (0);
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
