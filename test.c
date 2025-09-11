/*
// Add these to your header file defines
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WALL_HEIGHT 32  // Same as TILE_SIZE typically

// Colors for different elements
#define CEILING_COLOR 0x87CEEBFF  // Sky blue
#define FLOOR_COLOR 0x8B4513FF    // Brown
#define WALL_COLOR_NS 0x808080FF  // Gray for North/South walls
#define WALL_COLOR_EW 0x606060FF  // Darker gray for East/West walls

void draw_3d_walls(t_game *game) {
    // Calculate how many pixels each ray covers on screen
    float rays_per_pixel = (float)NUM_RAYS / SCREEN_WIDTH;
    
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Map screen column to ray index
        int ray_index = (int)(x * rays_per_pixel);
        if (ray_index >= NUM_RAYS) ray_index = NUM_RAYS - 1;
        
        t_ray *ray = &game->ray[ray_index];
        
        // Skip rays that didn't hit anything
        if (ray->distance >= FLT_MAX) {
            // Draw sky column
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                mlx_put_pixel(game->img, x, y, CEILING_COLOR);
            }
            continue;
        }
        
        // Calculate projected wall height
        float projected_height = (WALL_HEIGHT * SCREEN_HEIGHT) / ray->distance;
        
        // Calculate wall boundaries
        int wall_top = (int)((SCREEN_HEIGHT - projected_height) / 2);
        int wall_bottom = (int)((SCREEN_HEIGHT + projected_height) / 2);
        
        // Clamp to screen bounds
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= SCREEN_HEIGHT) wall_bottom = SCREEN_HEIGHT - 1;
        
        // Choose wall color based on wall orientation
        uint32_t wall_color = ray->wasHitVertical ? WALL_COLOR_NS : WALL_COLOR_EW;
        
        // Draw the vertical strip
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            uint32_t color;
            
            if (y < wall_top) {
                // Ceiling
                color = CEILING_COLOR;
            } else if (y >= wall_top && y <= wall_bottom) {
                // Wall
                color = wall_color;
            } else {
                // Floor
                color = FLOOR_COLOR;
            }
            
            mlx_put_pixel(game->img, x, y, color);
        }
    }
}

// Modified render function to support both 2D and 3D views
void render(t_game *game) {
    mlx_delete_image(game->mlx, game->img);
    
    // Create image with full screen dimensions for 3D view
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img) return;
    
    // Cast all rays first
    castAllRays(game);
    
    // Choose rendering mode (you can add a toggle later)
    int show_3d_view = 1; // Set to 0 for minimap, 1 for 3D
    
    if (show_3d_view) {
        draw_3d_walls(game);
        
        // Optional: Draw minimap overlay in corner
        draw_minimap_overlay(game);
    } else {
        // Original 2D minimap view
        draw_map(game);
    }
    
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}

// Optional: Draw minimap as small overlay in corner
void draw_minimap_overlay(t_game *game) {
    int minimap_scale = 4; // Scale factor for minimap
    int minimap_size = 150; // Size of minimap overlay
    int offset_x = 10;      // Position from left edge
    int offset_y = 10;      // Position from top edge
    
    // Draw minimap background
    for (int y = 0; y < minimap_size; y++) {
        for (int x = 0; x < minimap_size; x++) {
            mlx_put_pixel(game->img, offset_x + x, offset_y + y, 0x00000080); // Semi-transparent black
        }
    }
    
    // Draw simplified map
    for (int map_y = 0; map_y < game->m_height; map_y++) {
        for (int map_x = 0; map_x < game->m_width; map_x++) {
            int pixel_x = offset_x + (map_x * minimap_size) / game->m_width;
            int pixel_y = offset_y + (map_y * minimap_size) / game->m_height;
            int pixel_size = minimap_size / game->m_width;
            
            uint32_t color = (game->map[map_y][map_x] == '1') ? 0xFFFFFFFF : 0x000000FF;
            
            // Draw small rectangle for each map cell
            for (int dy = 0; dy < pixel_size && pixel_y + dy < offset_y + minimap_size; dy++) {
                for (int dx = 0; dx < pixel_size && pixel_x + dx < offset_x + minimap_size; dx++) {
                    mlx_put_pixel(game->img, pixel_x + dx, pixel_y + dy, color);
                }
            }
        }
    }
    
    // Draw player dot
    int player_pixel_x = offset_x + (int)((game->player.player_x / game->mini_map_tile) * minimap_size) / game->m_width;
    int player_pixel_y = offset_y + (int)((game->player.player_y / game->mini_map_tile) * minimap_size) / game->m_height;
    
    // Draw player as small square
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int px = player_pixel_x + dx;
            int py = player_pixel_y + dy;
            if (px >= offset_x && px < offset_x + minimap_size && 
                py >= offset_y && py < offset_y + minimap_size) {
                mlx_put_pixel(game->img, px, py, 0xFF0000FF); // Red player dot
            }
        }
    }
}

// Update your init_cub_window to use screen dimensions
int init_cub_window(t_game *game) {
    game->m_width = 15;
    game->m_height = 11;
    game->player.is_init = 0;
    
    // Keep minimap calculations for collision detection
    int window_width = game->m_width * TILE_SIZE;
    int window_height = game->m_height * TILE_SIZE;
    game->mini_map_width = (int)(window_width * MINI_MAP_VECTOR);
    game->mini_map_height = (int)(window_height * MINI_MAP_VECTOR);
    game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);

    game->ray = gc_malloc(game->gc, sizeof(t_ray) * NUM_RAYS);
    if (!game->ray) {
        printf("Failed to allocate to ray \n");
        return 0;
    }
    
    for (int i = 0; i < NUM_RAYS; i++) {
        game->ray[i].distance = FLT_MAX;
        game->ray[i].wallHitX = 0;
        game->ray[i].wallHitY = 0;
        game->ray[i].wasHitVertical = 0;
    }
    
    game->player.player_x = 0;
    game->player.player_y = 0;
    game->player.p_width = 2;
    game->player.p_height = 2;
    game->last_frame_ms = get_current_time();
    
    // Create window with screen dimensions for 3D view
    game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    if (!game->mlx) {
        return 0;
    }
    
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img) {
        mlx_terminate(game->mlx);
        return 0;
    }
    
    draw_map(game); // Initial draw
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    
    return 1;
}
*/