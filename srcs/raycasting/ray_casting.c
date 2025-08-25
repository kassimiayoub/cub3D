/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/25 14:24:41 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3D.h"

// void draw_line_askour(mlx_image_t *img, int x0, int y0, int x1, int y1, uint16_t line_color){
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1;
// 	int sy = (y0 < y1) ? 1 : -1;
// 	int err = dx - dy;

// 	while (1){
// 		if (x0 >= 0 && x0 < (int)img->width && y0 >= 0 && y0 < (int)img->height){
// 			mlx_put_pixel(img, x0, y0, line_color);
// 		}

// 		if (x0 == x1 && y0 == y1) break;

// 		int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
// 	}	
// }

// void draw_player_direction(t_game *game){
// 	float ray_len = 40;
// 	uint32_t ray_color = 0xFF0000FF;


// 	int end_x = (int)(game->player.player_x + cos(game->player.rotationAngle) * ray_len) ;
// 	int end_y = (int)(game->player.player_y + sin(game->player.rotationAngle) * ray_len) ;

// 	draw_line_askour(game->img, game->player.player_x , game->player.player_y, end_x, end_y, ray_color);
// }

// void draw_player(t_game *game){

// 	printf("the  px is : %f\n", game->player.player_x);
// 	printf("the  py is : %f\n", game->player.player_y);
// 	int player_size = 3;
// 	uint32_t  player_color = 0x00FF00FF;

// 	for (int i = -player_size; i <= player_size; i++){
// 			for (int j = -player_size; j <= player_size; j++){
// 				int px = (int)game->player.player_x + i;
// 				int py = (int)game->player.player_y + j;
// 				if (px >= 0 && px < game->mini_map_width && py >= 0 && py < game->mini_map_height){
// 						mlx_put_pixel(game->img, px, py, player_color);
// 				}
// 			}
// 	}
// }

// void draw_map(t_game *game ){
// 	for (int y = 0; y < game->m_height; y++)
// 	{
// 		for (int x = 0; x < game->m_width; x++)
// 		{
// 			uint32_t color; 
// 			if (game->map[y][x] == '1')
// 				color = 0xFF0000FF;
// 			else if (game->map[y][x] == 'W'){
// 				/// @brief color for player over here
// 				color = 0xFFFFFFFF;
// 				if (game->player.player_x == 0 && game->player.player_y == 0){
// 					printf("ana hna :\n");
// 					game->player.player_x = (x * game->mini_map_tile) + (game->mini_map_tile / 2);
// 					game->player.player_y = (y * game->mini_map_tile) + (game->mini_map_tile / 2);
// 					game->player.p_width = 5;
// 					game->player.p_height = 5;
// 					game->player.turnDirection = 0;
// 					game->player.walkDirection = 0;
// 					game->player.rotationAngle = M_PI / 2;
// 					game->player.walkSpeed = 300;
// 					game->player.turnSpeed = 5 * (M_PI / 180);
// 				}
// 			}	
// 			else 
// 				color = 0xFFFFFFFF;
// 			for (int i = 0; i < game->mini_map_tile; i++)
// 			{
// 				for (int j = 0; j < game->mini_map_tile; j++)
// 						mlx_put_pixel(game->img, x * game->mini_map_tile + i, y * game->mini_map_tile + j, color);
// 			}
// 		}
// 	}
// 	// drawing player
// 	draw_player(game);
// 	draw_player_direction(game);
// }


// void render(t_game *game){
// 	// int window_width = game->m_width * TILE_SIZE;
// 	// int window_height = game->m_height * TILE_SIZE;


// 	printf("the player_x is : %f | and the player_y is : %f\n", game->player.player_x, game->player.player_y);
// 	mlx_delete_image(game->mlx, game->img);
// 	game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
// 	/// @brief redraw map
// 	draw_map(game);
// 	// /// @brief redraw play
// 	// redraw_player(game);

// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// }

// int check_for_collision(t_game *game, int newPlayerX, int newPlayerY) {
//     int map_x = newPlayerX / game->mini_map_tile;
//     int map_y = newPlayerY / game->mini_map_tile;

//     if (map_x < 0 || map_x >= game->mini_map_width ||
//         map_y < 0 || map_y >= game->mini_map_height)
//         return 1;

//     if (game->map[map_y][map_x] == '1')
//         return 1;

//     return 0;
// }


// // void key_handler(mlx_key_data_t data, void* arg){
// // 	t_game *game = (t_game *)arg;
// // 	float move_s = 5.0f;  /// pixels per frame

// // 	int new_player_x = game->player.player_x;
// // 	int new_player_y = game->player.player_y;

// // 	if (data.action == MLX_PRESS || data.action == MLX_REPEAT){
// // 		if(data.key == MLX_KEY_W || data.key == MLX_KEY_UP)
// // 		{
// // 			new_player_x += cos(game->player.rotationAngle) * move_s;
// // 			new_player_y += sin(game->player.rotationAngle) * move_s;
// // 		}
// // 		else if(data.key == MLX_KEY_S || data.key == MLX_KEY_DOWN)
// // 		{
// // 			new_player_x -= cos(game->player.rotationAngle) * move_s;
// // 			new_player_y -= sin(game->player.rotationAngle) * move_s; 
// // 		}
// // 		else if(data.key == MLX_KEY_A || data.key == MLX_KEY_LEFT)
// // 			game->player.rotationAngle -= game->player.turnSpeed;
// // 		else if(data.key == MLX_KEY_D || data.key == MLX_KEY_RIGHT)
// // 			game->player.rotationAngle += game->player.turnSpeed;
// // 		else if (data.key == MLX_KEY_SPACE){
// // 			mlx_close_window(game->mlx);
// // 			return;
// // 		}
// // 	}


// // 	/// @brief i will normalize the angel to keep ti between 0 and 2PI
// // 	if (game->player.rotationAngle < 0)
// // 		game->player.rotationAngle += 2 * M_PI;
// // 	if (game->player.rotationAngle >= 2 * M_PI)
// // 		game->player.rotationAngle -= 2 * M_PI;

// // 	/// @brief before i render may map again i will check for boundary and walls

// // 	if (!check_for_collision(game, new_player_x, new_player_y)){
// // 		printf("render again\n");
// // 		game->player.player_x = new_player_x;
// // 		game->player.player_y = new_player_y;
// // 		render(game);
// // 	}
// // }


// long	getcurrenttime(void)
// {
// 	struct timeval	eval;

// 	if (gettimeofday(&eval, NULL) == -1)
// 		return (printf("error geting time in ms\n"), 1);
// 	return (eval.tv_sec * 1000 + eval.tv_usec / 1000);
// }

// void proccess_input(mlx_key_data_t data, t_game *game){
// 	if (data.action == MLX_PRESS){
// 		if (data.key == MLX_KEY_UP || data.key == MLX_KEY_W)
// 			game->player.walkDirection = 1;
// 		else if (data.key == MLX_KEY_DOWN || data.key == MLX_KEY_S)
// 			game->player.walkDirection = -1;
// 		else if (data.key == MLX_KEY_RIGHT || data.key == MLX_KEY_D)
// 			game->player.turnDirection = 1;
// 		else if (data.key == MLX_KEY_LEFT || data.key == MLX_KEY_A)
// 			game->player.turnDirection = -1;
// 	}
// 	else if (data.action == MLX_RELEASE){
// 		if (data.key == MLX_KEY_UP || data.key == MLX_KEY_W || 
// 		    data.key == MLX_KEY_DOWN || data.key == MLX_KEY_S)
// 			game->player.walkDirection = 0;
// 		else if (data.key == MLX_KEY_RIGHT || data.key == MLX_KEY_D || 
// 		         data.key == MLX_KEY_LEFT || data.key == MLX_KEY_A)
// 			game->player.turnDirection = 0;
// 	}
// }

// void move_player(t_game *game, long deltaTime){
// 	float deltaTimeSec = deltaTime / 1000.0f;
	

// 	game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed * deltaTimeSec;
	

// 	if (game->player.rotationAngle < 0)
// 		game->player.rotationAngle += 2 * M_PI;
// 	if (game->player.rotationAngle >= 2 * M_PI)
// 		game->player.rotationAngle -= 2 * M_PI;
	

// 	float moveStep = game->player.walkDirection * game->player.walkSpeed * deltaTimeSec;
// 	float newPlayerX = game->player.player_x + cos(game->player.rotationAngle) * moveStep;
// 	float newPlayerY = game->player.player_y + sin(game->player.rotationAngle) * moveStep;

// 	if (!check_for_collision(game, (int)newPlayerX, (int)newPlayerY)){
// 		game->player.player_x = newPlayerX;
// 		game->player.player_y = newPlayerY;
// 	}
// }

// void update(mlx_key_data_t data, void *arg){
// 	(void)data;
// 	t_game *game = (t_game *)arg;

// 	long now = getcurrenttime();
// 	if (now < game->last_frame_ms + FRAME_TIME_LENGHT) 
// 		return;

// 	long deltaTime = now - game->last_frame_ms; 
// 	game->last_frame_ms = now;
	
// 	proccess_input(data, game);
// 	move_player(game, deltaTime);
// 	render(game);  
// }

// int init_cub_window(t_game *game) {
// 	game->m_height = 11;
// 	game->m_width = 15;

// 	int window_width = game->m_width * TILE_SIZE;
// 	int window_height = game->m_height * TILE_SIZE;
// 	game->player.player_x = 0;
// 	game->player.player_y = 0;
// 	game->last_frame_ms = getcurrenttime();


// 	///@brief mini map dimmision 
// 	game->mini_map_width = (int)(window_width * MINI_MAP_VECTOR);
// 	game->mini_map_height = (int)(window_height * MINI_MAP_VECTOR);
// 	game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);
	

// 	game->mlx = mlx_init( window_width, window_height, "CUB3D", true);
// 	if (!game->mlx){
// 		printf("mlx failed to init\n");
// 		return 0;
// 	}
// 	game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
// 	if (!game->img){
// 		printf("somethin worring with image over here\n");
// 		return 0;
// 	}
// 	draw_map(game);

// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// 	mlx_key_hook(game->mlx, &update, game);
// 	mlx_loop(game->mlx);
// 	mlx_terminate(game->mlx);
// 	return 1;
// }

#include "cub3D.h"

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

float  distanceBetweenPoints (float x1, float  y1, float x2, float  y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}


void draw_line_dda(mlx_image_t *img, float x0, float y0, float x1, float y1, uint32_t color) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    
    int steps = (int)(fmax(fabs(dx), fabs(dy)));
    
    if (steps == 0) {
        if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height) {
            mlx_put_pixel(img, (int)x0, (int)y0, color);
        }
        return;
    }
    
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    
    float x = x0;
    float y = y0;
    
    for (int i = 0; i <= steps; i++) {
        int px = (int)(x + 0.5f);
        int py = (int)(y + 0.5f);
        
        if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height) {
            mlx_put_pixel(img, px, py, color);
        }
        
        x += x_inc;
        y += y_inc;
    }
}

void    draw_line(void *win, int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

   int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        mlx_put_pixel(win, x1, y1, color);
        return;
    }

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        if (round(x) >= 0 && round(x) < 800 && round(y) >= 0 && round(y) < 600) { // Adjust bounds as needed
            mlx_put_pixel(win, round(x), round(y), color);
        }
        x += x_inc;
        y += y_inc;
    }
}

void draw_all_lines(t_game *game){
    uint32_t ray_color = 0xFF0000FF;
    for (int i = 0; i < NUM_RAYS; i++){
        if (game->ray[i].distance < FLT_MAX){    
                draw_line(game->img,
                (int)game->player.player_x,
                (int)game->player.player_y,
                (int)game->ray[i].wallHitX,
                (int)game->ray[i].wallHitY,
                ray_color);
        }
    } 
}


void draw_player_direction(t_game *game) {
    float ray_len = 80;
    uint32_t ray_color = 0xFF00EEFF;
    
    int end_x = (int)(game->player.player_x + cos(game->player.rotationAngle) * ray_len);
    int end_y = (int)(game->player.player_y + sin(game->player.rotationAngle) * ray_len);
    
    draw_line(game->img, (int)game->player.player_x, (int)game->player.player_y, end_x, end_y, ray_color);
}

void draw_player(t_game *game) {
    int player_size = 4;
    uint32_t player_color = 0x00FF00FF;
    
    for (int i = -player_size; i <= player_size; i++) {
        for (int j = -player_size; j <= player_size; j++) {
            int px = (int)game->player.player_x + i;
            int py = (int)game->player.player_y + j;
            if (px >= 0 && px < game->mini_map_width && py >= 0 && py < game->mini_map_height) {
                mlx_put_pixel(game->img, px, py, player_color);
            }
        }
    }
}

void init_player_position(t_game *game, int x, int y) {
    if (game->player.player_x == 0 && game->player.player_y == 0) {
        game->player.player_x = (x * game->mini_map_tile) + (game->mini_map_tile / 2);
        game->player.player_y = (y * game->mini_map_tile) + (game->mini_map_tile / 2);
        game->player.rotationAngle = M_PI / 2;
        game->player.walkSpeed = 100.0f;
        game->player.turnSpeed = 2.0f;
        game->player.walkDirection = 0;
        game->player.turnDirection = 0;
    }
}

float  normalizeAngle(float rayAngle){
    rayAngle = remainder(rayAngle, 2 * M_PI);
    if (rayAngle < 0)
        rayAngle = (2 * M_PI) + rayAngle;
    return rayAngle;
}

void castRay(t_game *game, float rayAngle, int stripId){
    rayAngle = normalizeAngle(rayAngle);
    int isRayFacingUp = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingDown = !isRayFacingUp;
    int isRayFacingRight = rayAngle < M_PI / 2 || rayAngle > 3 * M_PI / 2; 
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    /// @brief handle the horizontal wall hit logic first 
    int foundHorizontalWallHit = 0;
    float horizWallHitX = 0;
    float horizWallHitY = 0;
    int horizWallContent = 0;
    
    /// Find the y-coordinate of the closest horizo grid intersection (first point)
    yintercept = floor(game->player.player_y / game->mini_map_tile) * game->mini_map_tile;
    yintercept += isRayFacingDown ? game->mini_map_tile : 0;
    
    /// Find the x-coordinate of the closest horizo grid intersection (first point)
     if (fabs(tan(rayAngle)) < 0.0001) { // Avoid division by zero
        xintercept = game->player.player_x;
    } else {
        xintercept = game->player.player_x + (yintercept - game->player.player_y) / tan(rayAngle);
    }
    // xintercept = game->player.player_x + (yintercept - game->player.player_y) / tan(rayAngle);

    /// calculate the increment xstep and ystep 
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;
    
    if (fabs(tan(rayAngle)) < 0.0001) {
        xstep = 0; // Ray is horizontal
    } else {
        xstep = game->mini_map_tile / tan(rayAngle);
        xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
        xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
    }

    // xstep = TILE_SIZE / tan(rayAngle);
    // xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    // xstep *=  (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorizTouchX = xintercept; 
    float nextHorizTouchY = yintercept;

    while (nextHorizTouchX >= 0 && nextHorizTouchX < game->mini_map_width && nextHorizTouchX >= 0 && nextHorizTouchY < game->mini_map_height){
        float xToCheck = nextHorizTouchX;
        float yToCheck = nextHorizTouchY + (isRayFacingUp ? -1 : 0);
        if (check_for_collision(game, xToCheck, yToCheck)){
            horizWallHitX = nextHorizTouchX;
            horizWallHitY = nextHorizTouchY;
            // horizWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorizontalWallHit = 1;
            break;
        }else {
            nextHorizTouchX += xstep;
            nextHorizTouchY += ystep;
        }
    }

    /// @brief handle the vertical wall hit logic 
    int foundVertWallHit = 0;
    float wallVertHitX = 0;
    float wallVertHitY = 0;


    xintercept = floor(game->player.player_x / game->mini_map_tile) * game->mini_map_tile;
    xintercept += isRayFacingRight ? game->mini_map_tile : 0;

    if (fabs(cos(rayAngle)) < 0.0001) { 
        yintercept = game->player.player_y;
    } else {
        yintercept = game->player.player_y + (xintercept - game->player.player_x) * tan(rayAngle);
    }

    // yintercept = game->player.player_y + (xintercept - game->player.player_x) * tan(rayAngle);

    xstep = game->mini_map_tile;
    xstep *= isRayFacingLeft ? -1 : 1;
    
    if (fabs(cos(rayAngle)) < 0.0001) {
        ystep = 0;
    } else {
        ystep = game->mini_map_tile * tan(rayAngle);
        ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
        ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
    }

    // ystep = TILE_SIZE * tan(rayAngle);
    // ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    // ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float  nextVertTouchY = yintercept;

    
    while (nextVertTouchX >= 0 && nextVertTouchX < game->mini_map_width && nextVertTouchY >= 0 && nextVertTouchY <
        game->mini_map_height
    ) {

        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        if (check_for_collision(game, xToCheck, yToCheck)) {
            foundVertWallHit = 1;
            wallVertHitX = nextVertTouchX;
            wallVertHitY = nextVertTouchY;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }
    float horizHitDistance = (foundHorizontalWallHit)
    ? distanceBetweenPoints(game->player.player_x, game->player.player_y, horizWallHitX, horizWallHitY)
    : FLT_MAX;
    float vertHitDistance = (foundVertWallHit)
    ? distanceBetweenPoints(game->player.player_x, game->player.player_y, wallVertHitX, wallVertHitY) 
    : FLT_MAX;

    if (vertHitDistance < horizHitDistance){
        printf("verHitDistance < horizHitDistance\n");
        game->ray[stripId].wallHitX = wallVertHitX;
        game->ray[stripId].wallHitY = wallVertHitY;
        game->ray[stripId].distance = vertHitDistance;
        game->ray[stripId].wasHitVertical = 1;
    }else {
        game->ray[stripId].wallHitX = horizWallHitX;
        game->ray[stripId].wallHitY = horizWallHitY;
        game->ray[stripId].distance = horizHitDistance;
        game->ray[stripId].wasHitVertical = 0;
        game->ray[stripId].wallHitContent = horizWallContent;
    }

    game->ray[stripId].rayAngle = rayAngle;
    game->ray[stripId].isRayFacingDown = isRayFacingDown;
    game->ray[stripId].isRayFacingUp = isRayFacingUp;
    game->ray[stripId].isRayFacingLeft = isRayFacingLeft ;
    game->ray[stripId].isRayFacingRight = isRayFacingRight;
}

void castAllRays(t_game *game){
    float rayAngle = game->player.rotationAngle - (FOV_ANGLE / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++){
        printf("am over here\n");
        castRay(game, rayAngle, stripid);
        rayAngle += FOV_ANGLE / NUM_RAYS;
    }
}

void draw_map(t_game *game) {
    for (int y = 0; y < game->m_height; y++) {
        for (int x = 0; x < game->m_width; x++) {
            uint32_t color;
            
            if (game->map[y][x] == '1') {
                color = 0x000000FF;
            } else if (game->player.is_init == 0 && (game->map[y][x] == 'N' || game->map[y][x] == 'S' || 
                      game->map[y][x] == 'E' || game->map[y][x] == 'W')) {
                color = 0xFFFFFFFF;
                init_player_position(game, x, y);
				game->player.is_init = 1;
                if (game->map[y][x] == 'N') game->player.rotationAngle = 3 * M_PI / 2;
                else if (game->map[y][x] == 'S') game->player.rotationAngle = M_PI / 2;
                else if (game->map[y][x] == 'E') game->player.rotationAngle = 0;
                else if (game->map[y][x] == 'W') game->player.rotationAngle = M_PI;
            } else {
                color = 0xFFFFFFFF;
            }
            
            for (int i = 0; i < game->mini_map_tile; i++) {
                for (int j = 0; j < game->mini_map_tile; j++) {
                    int px = x * game->mini_map_tile + i;
                    int py = y * game->mini_map_tile + j;
                    if (px < game->mini_map_width && py < game->mini_map_height) {
                        mlx_put_pixel(game->img, px, py, color);
                    }
                }
            }
        }
    }
    castAllRays(game);
    draw_all_lines(game);
    draw_player(game);
    draw_player_direction(game);
}

void render(t_game *game) {
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
    if (!game->img) return;
    
    draw_map(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int is_wall(t_game *game, float x, float y) {
    int map_x = (int)(x / game->mini_map_tile);
    int map_y = (int)(y / game->mini_map_tile);
    
    if (map_x < 0 || map_x >= game->m_width || 
        map_y < 0 || map_y >= game->m_height) {
        return 1;
    }
    
    return (game->map[map_y][map_x] == '1');
}

long get_current_time(void) {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) {
        return 0;
    }
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void process_input(t_game *game) {
    game->player.walkDirection = 0;
    game->player.turnDirection = 0;
    
    if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP)) {
        game->player.walkDirection = 1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN)) {
        game->player.walkDirection = -1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) {
        game->player.turnDirection = -1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) {
        game->player.turnDirection = 1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
        game->player.turnDirection = -1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
        game->player.turnDirection = 1;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) {
        mlx_close_window(game->mlx);
    }
}

void update_player(t_game *game, float delta_time) {
    if (game->player.turnDirection != 0) {
        game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed * delta_time;
		printf("the palyer rotation angle is : %f\n", game->player.rotationAngle);
        while (game->player.rotationAngle < 0) {
            game->player.rotationAngle += 2 * M_PI;
        }
        while (game->player.rotationAngle >= 2 * M_PI) {
            game->player.rotationAngle -= 2 * M_PI;
        }
    }
    if (game->player.walkDirection != 0) {
        float move_step = game->player.walkDirection * game->player.walkSpeed * delta_time;
        float new_x = game->player.player_x + cos(game->player.rotationAngle) * move_step;
        float new_y = game->player.player_y + sin(game->player.rotationAngle) * move_step;

		if (!check_for_collision(game, new_x, new_y)){
			printf("render again\n");
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
       
    }
}

void game_loop(void *param) {
    t_game *game = (t_game *)param;
    
    long now = get_current_time();
    float delta_time = (now - game->last_frame_ms) / 1000.0f;
    if (delta_time < 0.016f) {
        return;
    }
    
    game->last_frame_ms = now;
    
    process_input(game);
    update_player(game, delta_time);
    render(game);
}

int init_cub_window(t_game *game) {
    game->m_width = 15;
    game->m_height = 11;
	game->player.is_init = 0;
    
    int window_width = game->m_width * TILE_SIZE;
    int window_height = game->m_height * TILE_SIZE;
    
    game->mini_map_width = (int)(window_width * MINI_MAP_VECTOR);
    game->mini_map_height = (int)(window_height * MINI_MAP_VECTOR);
    game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);
    
    game->player.player_x = 0;
    game->player.player_y = 0;
    game->last_frame_ms = get_current_time();
    
    game->mlx = mlx_init(window_width, window_height, "cub3D", true);
    if (!game->mlx) {
        return 0;
    }
    
    game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
    if (!game->img) {
        mlx_terminate(game->mlx);
        return 0;
    }
    
    draw_map(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    
    return 1;
}