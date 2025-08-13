/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:15:21 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 17:50:26 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	allocation_initial_struct(t_game **game)
{
	(*game)->gc = malloc(sizeof(t_gc));
	if (!(*game)->gc)
		return (0);
	(*game)->gc->head = NULL;
	(*game)->m_height = 0;
	(*game)->m_width = 0;
	(*game)->is_player = 0;
	(*game)->no_path = NULL;
	(*game)->ea_path = NULL;
	(*game)->so_path = NULL;
	(*game)->we_path = NULL;
	(*game)->c_color = NULL;
	(*game)->f_color = NULL;
	return (1);
}

void	f(void)
{
	system("leaks cub3D");
	system("lsof -c cub3D");
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		i;

	atexit(f);
	if (ac != 2)
		return (printf("Erreurn (nbr param!!)\n"), 1);
	if (!map_extension(av[1]))
		return (printf("Erreurn (extension nnot .cub!!)\n"), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (printf("Erreurn (allocation failed!!)\n"), 1);
	if (!allocation_initial_struct(&game))
		return (printf("Erreurn (allocation_initial_struct!!)\n"), 1);
	if (!read_map(&game, av[1]))
		return (printf("Erreurn (read_map!!)\n"), 1);
	i = 0;
	while (game->map[i])
	{
		printf("[%s]\n", game->map[i]);
		i++;
	}
	printf("*********************************************\n");
	i = 0;
	while (game->paths[i])
	{
		printf("=> [%s]\n", game->paths[i]);
		i++;
	}
	printf("*********************************************\n");
	printf("no_path -> %s\n", game->no_path);
	printf("so_path -> %s\n", game->so_path);
	printf("we_path -> %s\n", game->we_path);
	printf("ea_path -> %s\n", game->ea_path);
	printf("c_path -> %s\n", game->c_color);
	printf("f_path -> %s\n", game->f_color);
	gc_clear(game->gc);
	free(game->gc);
	free(game);
	return (0);
}
