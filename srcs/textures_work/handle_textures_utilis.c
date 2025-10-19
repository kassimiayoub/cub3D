/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures_utilis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:03:40 by aykassim          #+#    #+#             */
/*   Updated: 2025/10/18 16:05:12 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	ft_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	make_textures(mlx_t *mlx, char *path, mlx_image_t **texture)
{
	mlx_texture_t	*tmp;

	tmp = mlx_load_png(path);
	if (!tmp)
		return (0);
	(*texture) = mlx_texture_to_image(mlx, tmp);
	if (!(*texture))
	{
		mlx_delete_texture(tmp);
		return (0);
	}
	mlx_delete_texture(tmp);
	return (1);
}

int	load_images(t_game **game)
{
	if (!make_textures((*game)->mlx, (*game)->no_path, &(*game)->no_texture)
		|| !make_textures((*game)->mlx, (*game)->so_path, &(*game)->so_texture)
		|| !make_textures((*game)->mlx, (*game)->we_path, &(*game)->we_texture)
		|| !make_textures((*game)->mlx, (*game)->ea_path, &(*game)->ea_texture))
		return (0);
	return (1);
}

int	check_path_img(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (close (fd), 0);
	close(fd);
	return (1);
}

int	check_all_pathimg(t_game *game)
{
	if (!game || !game->ea_path || !game->so_path
		|| !game->we_path || !game->no_path)
		return (0);
	if (!check_path_img(game->ea_path) || !check_path_img(game->so_path)
		|| !check_path_img(game->we_path) ||!check_path_img(game->no_path))
		return (0);
	return (1);
}
