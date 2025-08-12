/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:15:21 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/12 16:03:27 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game *game;

	if (ac != 2)
		return (printf("Erreurn (nbr param!!)\n"), 1);
	if (!map_extension(av[1]))
		return (printf("Erreurn (extension nnot .cub!!)\n"), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (printf("Erreurn (allocation failed!!)\n"), 1);
	game->m_height = 0;
	game->m_width = 0;
	game->is_player = 0;
	if (!read_map(&game, av[1]))
		return (printf("Erreurn (read_map!!)\n"), 1);
	int i = 0;
	while (game->map[i])
	{
		printf("[%s]\n",game->map[i]);
		i++;
	}
	printf("height -> %d\n",game->m_height);
	printf("width -> %d\n",game->m_width);
	printf("is_player -> %d\n",game->is_player);
	return (0);
}