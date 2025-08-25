/*
#include "cub3D.h"
#include <float.h>  // For FLT_MAX

int check_for_collision(t_game *game, float newPlayerX, float newPlayerY) {
    int map_x = (int)(newPlayerX / game->mini_map_tile);
    int map_y = (int)(newPlayerY / game->mini_map_tile);

    if (map_x < 0 || map_x >= game->m_width ||
        map_y < 0 || map_y >= game->m_height)
        return 1;

    if (game->map[map_y][map_x] == '1')
        return 1;

    return 0;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void draw_line(void *win, int x1, int y1, int x2, int y2, int color) {
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

void draw_all_lines(t_game *game) {
    uint32_t ray_color = 0xFF0000FF; // Red rays
    
    for (int i = 0; i < NUM_RAYS; i++) {
        // Only draw if we found a valid hit
        if (game->ray[i].distance < FLT_MAX) {
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
    uint32_t ray_color = 0xFF00EEFF; // Cyan for player direction
    
    int end_x = (int)(game->player.player_x + cos(game->player.rotationAngle) * ray_len);
    int end_y = (int)(game->player.player_y + sin(game->player.rotationAngle) * ray_len);
    
    draw_line(game->img, (int)game->player.player_x, (int)game->player.player_y, end_x, end_y, ray_color);
}

void draw_player(t_game *game) {
    int player_size = 4; // Bigger player for visibility
    uint32_t player_color = 0x00FF00FF; // Green
    
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
        game->player.turnSpeed = 2.0f; // Fixed turn speed
        game->player.walkDirection = 0;
        game->player.turnDirection = 0;
    }
}

float normalizeAngle(float rayAngle) {
    rayAngle = remainder(rayAngle, 2 * M_PI);
    if (rayAngle < 0)
        rayAngle = (2 * M_PI) + rayAngle;
    return rayAngle;
}

void castRay(t_game *game, float rayAngle, int stripId) {
    rayAngle = normalizeAngle(rayAngle);
    int isRayFacingUp = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingDown = !isRayFacingUp;
    int isRayFacingRight = rayAngle < M_PI / 2 || rayAngle > 3 * M_PI / 2;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    // HORIZONTAL WALL HIT LOGIC
    int foundHorizontalWallHit = 0;
    float horizWallHitX = 0;
    float horizWallHitY = 0;
    int horizWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(game->player.player_y / game->mini_map_tile) * game->mini_map_tile;
    yintercept += isRayFacingDown ? game->mini_map_tile : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    if (fabs(tan(rayAngle)) < 0.0001) { // Avoid division by zero
        xintercept = game->player.player_x;
    } else {
        xintercept = game->player.player_x + (yintercept - game->player.player_y) / tan(rayAngle);
    }

    // Calculate the increment xstep and ystep
    ystep = game->mini_map_tile;
    ystep *= isRayFacingUp ? -1 : 1;

    if (fabs(tan(rayAngle)) < 0.0001) {
        xstep = 0; // Ray is horizontal
    } else {
        xstep = game->mini_map_tile / tan(rayAngle);
        xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
        xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
    }

    float nextHorizTouchX = xintercept;
    float nextHorizTouchY = yintercept;

    // FIXED: Use proper boundary checks with pixel coordinates
    while (nextHorizTouchX >= 0 && nextHorizTouchX < game->mini_map_width && 
           nextHorizTouchY >= 0 && nextHorizTouchY < game->mini_map_height) {
        
        float xToCheck = nextHorizTouchX;
        float yToCheck = nextHorizTouchY + (isRayFacingUp ? -1 : 0);
        
        if (check_for_collision(game, xToCheck, yToCheck)) {
            horizWallHitX = nextHorizTouchX;
            horizWallHitY = nextHorizTouchY; // FIXED: Store Y coordinate properly
            foundHorizontalWallHit = 1;
            break;
        }
        
        nextHorizTouchX += xstep;
        nextHorizTouchY += ystep;
    }

    // VERTICAL WALL HIT LOGIC
    int foundVertWallHit = 0;
    float wallVertHitX = 0;
    float wallVertHitY = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(game->player.player_x / game->mini_map_tile) * game->mini_map_tile;
    xintercept += isRayFacingRight ? game->mini_map_tile : 0;

    // Find the y-coordinate of the closest vertical grid intersection
   

    xstep = game->mini_map_tile;
    xstep *= isRayFacingLeft ? -1 : 1;

    if (fabs(cos(rayAngle)) < 0.0001) {
        ystep = 0; // Ray is vertical
    } else {
        ystep = game->mini_map_tile * tan(rayAngle);
        ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
        ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
    }

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // FIXED: Use proper boundary checks
    while (nextVertTouchX >= 0 && nextVertTouchX < game->mini_map_width && 
           nextVertTouchY >= 0 && nextVertTouchY < game->mini_map_height) {
        
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (check_for_collision(game, xToCheck, yToCheck)) {
            foundVertWallHit = 1;
            wallVertHitX = nextVertTouchX;
            wallVertHitY = nextVertTouchY;
            break;
        }
        
        nextVertTouchX += xstep;
        nextVertTouchY += ystep;
    }

    // Calculate distances and choose closest hit
    float horizHitDistance = foundHorizontalWallHit
        ? distanceBetweenPoints(game->player.player_x, game->player.player_y, horizWallHitX, horizWallHitY)
        : FLT_MAX;
        
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(game->player.player_x, game->player.player_y, wallVertHitX, wallVertHitY)
        : FLT_MAX;

    // Store the closest hit in the ray array
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
    
    // Store ray angle and direction info
    game->ray[stripId].rayAngle = rayAngle;
    game->ray[stripId].isRayFacingUp = isRayFacingUp;
    game->ray[stripId].isRayFacingDown = isRayFacingDown;
    game->ray[stripId].isRayFacingLeft = isRayFacingLeft;
    game->ray[stripId].isRayFacingRight = isRayFacingRight;
}

void castAllRays(t_game *game) {
    float rayAngle = game->player.rotationAngle - (FOV_ANGLE / 2);
    
    for (int stripid = 0; stripid < NUM_RAYS; stripid++) {
        castRay(game, rayAngle, stripid);
        rayAngle += FOV_ANGLE / NUM_RAYS;
    }
}

void draw_map(t_game *game) {
    for (int y = 0; y < game->m_height; y++) {
        for (int x = 0; x < game->m_width; x++) {
            uint32_t color;
            
            if (game->map[y][x] == '1') {
                color = 0x000000FF; // Black walls
            } else if (game->player.is_init == 0 && (game->map[y][x] == 'N' || game->map[y][x] == 'S' || 
                      game->map[y][x] == 'E' || game->map[y][x] == 'W')) {
                color = 0xFFFFFFFF; // White floor
                init_player_position(game, x, y);
                game->player.is_init = 1;
                
                // Set initial rotation based on spawn direction
                if (game->map[y][x] == 'N') game->player.rotationAngle = 3 * M_PI / 2;
                else if (game->map[y][x] == 'S') game->player.rotationAngle = M_PI / 2;
                else if (game->map[y][x] == 'E') game->player.rotationAngle = 0;
                else if (game->map[y][x] == 'W') game->player.rotationAngle = M_PI;
            } else {
                color = 0xFFFFFFFF; // White floor
            }
            
            // Draw the tile
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
    
    // Cast all rays first
    castAllRays(game);
    
    // Draw all rays
    draw_all_lines(game);
    
    // Draw player on top
    draw_player(game);
    
    // Draw player direction
    draw_player_direction(game);
}

// Rest of your functions remain the same...
void render(t_game *game) {
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->mini_map_width, game->mini_map_height);
    if (!game->img) return;
    
    draw_map(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
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
        
        // Normalize angle
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

        if (!check_for_collision(game, new_x, new_y)) {
            game->player.player_x = new_x;
            game->player.player_y = new_y;
        }
    }
}

void game_loop(void *param) {
    t_game *game = (t_game *)param;
    
    long now = get_current_time();
    float delta_time = (now - game->last_frame_ms) / 1000.0f;
    if (delta_time < 0.016f) { // ~60 FPS
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
*/