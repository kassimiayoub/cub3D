/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/24 09:02:12 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_player(t_game *game){

	printf("the  px is : %f\n", game->player.player_x);
	printf("the  py is : %f\n", game->player.player_y);
	int player_size = 3;
	uint32_t  player_color = 0x00FF00FF;

	for (int i = -player_size; i <= player_size; i++){
			for (int j = -player_size; j <= player_size; j++){
				int px = (int)game->player.player_x + i;
				int py = (int)game->player.player_y + j;
				if (px >= 0 && px < game->mini_map_width && py >= 0 && py < game->mini_map_height){
						mlx_put_pixel(game->img, px, py, player_color);
				}
			}
	}
}

void draw_map(t_game *game ){
	for (int y = 0; y < game->m_height; y++)
	{
		for (int x = 0; x < game->m_width; x++)
		{
			uint32_t color; 
			if (game->map[y][x] == '1')
				color = 0xFF0000FF;
			else if (game->map[y][x] == 'W'){
				/// @brief color for player over here
				color = 0xFFFFFFFF;
				if (game->player.player_x == 0 && game->player.player_y == 0){
					printf("ana hna :\n");
					game->player.player_x = (x * game->mini_map_tile) + (game->mini_map_tile / 2);
					game->player.player_y = (y * game->mini_map_tile) + (game->mini_map_tile / 2);
				}
			}	
			else 
				color = 0xFFFFFFFF;
			for (int i = 0; i < game->mini_map_tile; i++)
			{
				for (int j = 0; j < game->mini_map_tile; j++)
						mlx_put_pixel(game->img, x * game->mini_map_tile + i, y * game->mini_map_tile + j, color);
			}
		}
	}
	// drawing player
	draw_player(game);
}


void render(t_game *game){
	// int window_width = game->m_width * TILE_SIZE;
	// int window_height = game->m_height * TILE_SIZE;


	printf("the player_x is : %f | and the player_y is : %f\n", game->player.player_x, game->player.player_y);
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
	/// @brief redraw map
	draw_map(game);
	// /// @brief redraw play
	// redraw_player(game);

	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int check_for_collision(t_game *game, int newPlayerX, int newPlayerY) {
    int map_x = newPlayerX / game->mini_map_tile;
    int map_y = newPlayerY / game->mini_map_tile;

    if (map_x < 0 || map_x >= game->mini_map_width ||
        map_y < 0 || map_y >= game->mini_map_height)
        return 1;

    if (game->map[map_y][map_x] == '1')
        return 1;

    return 0;
}


void key_handler(mlx_key_data_t data, void* arg){
	t_game *game = (t_game *)arg;
	float move_s = 5.0f;  /// pixels per frame

	int new_player_x = game->player.player_x;
	int new_player_y = game->player.player_y;

	if (data.action == MLX_PRESS || data.action == MLX_REPEAT){
		if(data.key == MLX_KEY_W || data.key == MLX_KEY_UP)
			new_player_y  -= move_s;
		else if(data.key == MLX_KEY_S || data.key == MLX_KEY_DOWN)
			new_player_y  += move_s;
		else if(data.key == MLX_KEY_A || data.key == MLX_KEY_LEFT)
			new_player_x -= move_s;
		else if(data.key == MLX_KEY_D || data.key == MLX_KEY_RIGHT)
			new_player_x += move_s;
		else if (data.key == MLX_KEY_SPACE){
			mlx_close_window(game->mlx);
			return;
		}
	}

	/// @brief before i render may map again i will check for boundary and walls

	if (!check_for_collision(game, new_player_x, new_player_y)){
		printf("render again\n");
		game->player.player_x = new_player_x;
		game->player.player_y = new_player_y;
		render(game);
	}
}

int init_cub_window(t_game *game) {
	game->m_height = 11;
	game->m_width = 15;

	int window_width = game->m_width * TILE_SIZE;
	int window_height = game->m_height * TILE_SIZE;
	game->player.player_x = 0;
	game->player.player_y = 0;


	///@brief mini map dimmision 
	game->mini_map_width = (int)(window_width * MINI_MAP_VECTOR);
	game->mini_map_height = (int)(window_height * MINI_MAP_VECTOR);
	game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);
	

	game->mlx = mlx_init( window_width, window_height, "CUB3D", true);
	if (!game->mlx){
		printf("mlx failed to init\n");
		return 0;
	}
	game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
	if (!game->img){
		printf("somethin worring with image over here\n");
		return 0;
	}
	draw_map(game);

	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return 1;
}
