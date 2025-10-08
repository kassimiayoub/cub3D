/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:15:21 by aykassim          #+#    #+#             */
/*   Updated: 2025/10/04 12:57:10 by aykassim         ###   ########.fr       */
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

void	free_all(t_game *game)
{
	gc_clear(game->gc);
	free(game->gc);
	free(game);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_game	*game;

	if (ac != 2)
		return (printf("Erreurn (nbr param!!)\n"), 1);
	if (!map_extension(av[1]) )
		return (printf("Erreurn (extension nnot .cub!!)\n"), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (printf("error allocating game\n"), 0);
	if (!game || !allocation_initial_struct(&game))
		return (printf("Erreurn (allocation_initial_struct!!)\n"), 1);
	if (!read_map(&game, av[1]))
		return (printf("Erreurn (read_map!!)\n"), free_all(game), 1);
	if (!init(&game))
		return (printf("Erreurn (init!!)\n"), free_all(game), 1);
	game->mlx = mlx_init(game->win_width, game->win_height, "cub3D", false);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	if (!game->img)
		return (mlx_terminate(game->mlx), 0);
	if (!load_images(&game))
		return (printf("Erreur (load_images!!!)\n"), 0);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}
