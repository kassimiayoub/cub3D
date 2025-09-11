
#include "cub3D.h"

int check_for_collision(t_game *game, int newPlayerX, int newPlayerY) {
    int map_x = newPlayerX / game->mini_map_tile;
    int map_y = newPlayerY / game->mini_map_tile;

    if (map_x < 0 || map_x >= game->m_width ||
        map_y < 0 || map_y >= game->m_height)
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
    int rays_drawn = 0;
    for (int i = 0; i < NUM_RAYS; i++){
        if (game->ray[i].distance < FLT_MAX){    
                draw_line(game->img,
                (int)game->player.player_x,
                (int)game->player.player_y,
                (int)game->ray[i].wallHitX,
                (int)game->ray[i].wallHitY,
                ray_color);
                rays_drawn++;
        }
    } 
}


void draw_player_direction(t_game *game) {
    float ray_len = 20;
    uint32_t ray_color = 0x0000FF;
    
    int end_x = (int)(game->player.player_x + (cos(game->player.rotationAngle) * ray_len));
    int end_y = (int)(game->player.player_y + (sin(game->player.rotationAngle) * ray_len));
    
    draw_line(game->img, (int)game->player.player_x, (int)game->player.player_y, end_x, end_y, ray_color);
}

void draw_player(t_game *game) {
    int player_size = game->player.p_height * game->player.p_width;
    uint32_t player_color = 0x0000FF;
    
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
        game->player.player_x = (x * game->mini_map_tile) + (game->mini_map_tile / 2); /// this for putting the player in the middle of the grid
        game->player.player_y = (y * game->mini_map_tile) + (game->mini_map_tile / 2);
        game->player.walkSpeed = 200.0f;
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
    
    // For screen coordinates (Y increases downward)
    int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < M_PI / 2 || rayAngle > 3 * M_PI / 2; 
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    /// HORIZONTAL RAY-GRID INTERSECTION
    int foundHorizontalWallHit = 0;
    float horizWallHitX = 0;
    float horizWallHitY = 0;
    
    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(game->player.player_y / game->mini_map_tile) * game->mini_map_tile;
    yintercept += isRayFacingDown ? game->mini_map_tile : 0;
    
    // Find the x-coordinate of the closest horizontal grid intersection
    if (fabs(tan(rayAngle)) < 0.0001) { // Ray is horizontal
        xintercept = game->player.player_x;
        xstep = 0;
        ystep = isRayFacingUp ? -game->mini_map_tile : game->mini_map_tile;
    } else {
        xintercept = game->player.player_x + (yintercept - game->player.player_y) / tan(rayAngle);
        
        // Calculate steps - FIXED VERSION
        ystep = isRayFacingUp ? -game->mini_map_tile : game->mini_map_tile;
        xstep = ystep / tan(rayAngle);
        
        // Fix step signs
        if (isRayFacingLeft && xstep > 0) xstep = -xstep;
        if (isRayFacingRight && xstep < 0) xstep = -xstep;
    }

    float nextHorizTouchX = xintercept; 
    float nextHorizTouchY = yintercept;

    // Traverse horizontal grid lines
    while (nextHorizTouchX >= 0 && nextHorizTouchX < game->mini_map_width && 
           nextHorizTouchY >= 0 && nextHorizTouchY < game->mini_map_height) {
        
        float xToCheck = nextHorizTouchX;
        float yToCheck = nextHorizTouchY + (isRayFacingUp ? -1 : 0);
        
        if (check_for_collision(game, xToCheck, yToCheck)) {
            horizWallHitX = nextHorizTouchX;
            horizWallHitY = nextHorizTouchY;
            foundHorizontalWallHit = 1;
            break;
        } else {
            nextHorizTouchX += xstep;
            nextHorizTouchY += ystep;
        }
    }

    /// VERTICAL RAY-GRID INTERSECTION
    int foundVertWallHit = 0;
    float wallVertHitX = 0;
    float wallVertHitY = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(game->player.player_x / game->mini_map_tile) * game->mini_map_tile;
    xintercept += isRayFacingRight ? game->mini_map_tile : 0;

    if (fabs(cos(rayAngle)) < 0.0001) { // Ray is vertical
        yintercept = game->player.player_y;
        ystep = 0;
        xstep = isRayFacingLeft ? -game->mini_map_tile : game->mini_map_tile;
    } else {
        yintercept = game->player.player_y + (xintercept - game->player.player_x) * tan(rayAngle);
        
        // Calculate steps - FIXED VERSION
        xstep = isRayFacingLeft ? -game->mini_map_tile : game->mini_map_tile;
        ystep = xstep * tan(rayAngle);
        
        // Fix step signs
        if (isRayFacingUp && ystep > 0) ystep = -ystep;
        if (isRayFacingDown && ystep < 0) ystep = -ystep;
    }

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;
    
    // Traverse vertical grid lines
    while (nextVertTouchX >= 0 && nextVertTouchX < game->mini_map_width && 
           nextVertTouchY >= 0 && nextVertTouchY < game->mini_map_height) {
        
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

    // Calculate distances and choose the closer hit
    float horizHitDistance = foundHorizontalWallHit ? 
        distanceBetweenPoints(game->player.player_x, game->player.player_y, horizWallHitX, horizWallHitY) : FLT_MAX;
    float vertHitDistance = foundVertWallHit ? 
        distanceBetweenPoints(game->player.player_x, game->player.player_y, wallVertHitX, wallVertHitY) : FLT_MAX;

    if (vertHitDistance < horizHitDistance) {
        game->ray[stripId].wallHitX = wallVertHitX;
        game->ray[stripId].wallHitY = wallVertHitY;
        game->ray[stripId].distance = vertHitDistance;
        game->ray[stripId].wasHitVertical = 1;
    } else {
        game->ray[stripId].wallHitX = horizWallHitX;
        game->ray[stripId].wallHitY = horizWallHitY;
        game->ray[stripId].distance = horizHitDistance;
        game->ray[stripId].wasHitVertical = 0;
    }

    // Apply fisheye correction
    game->ray[stripId].distance *= cos(rayAngle - game->player.rotationAngle);
    game->ray[stripId].rayAngle = rayAngle;
    game->ray[stripId].isRayFacingDown = isRayFacingDown;
    game->ray[stripId].isRayFacingUp = isRayFacingUp;
    game->ray[stripId].isRayFacingLeft = isRayFacingLeft;
    game->ray[stripId].isRayFacingRight = isRayFacingRight;
}
/// @brief  amover here
/// @param game 
void castAllRays(t_game *game){
    if (!game || !game->map || !game->player.is_init)
        return ; 
    float rayAngle = game->player.rotationAngle - (FOV_ANGLE / 2);
    float angleStep = FOV_ANGLE / NUM_RAYS;
    for (int stripid = 0; stripid < NUM_RAYS; stripid++){
        castRay(game, rayAngle, stripid);
        rayAngle += angleStep;
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
                // color = 0xFFFFFFFF;
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
    draw_player_direction(game);
    draw_player(game);
}

void render(t_game *game) {
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
    if (!game->img) return;

    // castAllRays(game);

    int show_3d_view = 1 ; 
    if (show_3d_view){
        draw_map(game);
        draw_3D_wall(game);
    }else{
        draw_map(game);
    }
    
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

// void proccess_input(mlx_key_data_t data, t_game *game){

//     game->player.walkDirection = 0;
//     game->player.turnDirection = 0;
    
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

void process_input(t_game *game) {
    game->player.walkDirection = 0;
    game->player.turnDirection = 0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
        game->player.walkDirection = 1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
        game->player.walkDirection = -1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx, MLX_KEY_A))
        game->player.turnDirection = -1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(game->mlx, MLX_KEY_D))
        game->player.turnDirection = 1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
}

void update_player(t_game *game, float delta_time) {
    if (game->player.turnDirection != 0) {
        game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed * delta_time;
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

int init_cub_window( t_game *game) {
    game->m_width = 51;
    game->m_height = 20;
	game->player.is_init = 0;
    
    int window_width = game->m_width * TILE_SIZE;
    int window_height = game->m_height * TILE_SIZE;

    game->ray = gc_malloc(game->gc, sizeof(t_ray) * NUM_RAYS);
    if (!game->ray)
    {
        printf("Failed to allocate to ray \n");
        return 0;
    }
    for (int i = 0; i < NUM_RAYS; i++) {
        game->ray[i].distance = FLT_MAX;
        game->ray[i].wallHitX = 0;
        game->ray[i].wallHitY = 0;
        game->ray[i].wasHitVertical = 0;
        game->ray[i].isRayFacingUp = 0;
        game->ray[i].isRayFacingDown = 0;
        game->ray[i].isRayFacingLeft = 0;
        game->ray[i].isRayFacingRight = 0;
    }

    
    game->mini_map_width = (int)(window_width * MINI_MAP_VECTOR);
    game->mini_map_height = (int)(window_height * MINI_MAP_VECTOR);
    game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);
    
    game->player.player_x = 0;
    game->player.player_y = 0;
    game->player.p_width = 2;
    game->player.p_height = 2;
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