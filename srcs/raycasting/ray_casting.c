/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/21 17:09:33 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int init_cub_window(t_game *game) {
    game->m_height = 800;
    game->m_width = 500;

    void    *mlx;
    void    *win;
    int window_width = game->m_width;
    int window_height = game->m_height;
    

    mlx = mlx_init();
    if (!mlx){
        printf("mlx failed to init\n");
        return 0;
    }

    win = mlx_new_window(mlx, window_width, window_height, "CUB3D");
    if (!win){
        printf("creating window failed\n");
        return 0;
    }
    mlx_loop(mlx);
    return 1;
}
