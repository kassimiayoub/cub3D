
#include "cub3D.h"

void draw_3D_wall(t_game *game){
    int screen_width = game->m_width * TILE_SIZE;
    int screen_height = game->m_height * TILE_SIZE;
    
    float ray_per_pixel = (float)NUM_RAYS / screen_width;
    
    for (int x = 0; x < screen_width; x++){
        int ray_index = (int)(x * ray_per_pixel);
        if (ray_index >= NUM_RAYS)
            ray_index = NUM_RAYS - 1;
            
        t_ray *ray = &game->ray[ray_index];
        
        if (ray->distance >= FLT_MAX){
            for (int y = 0; y < screen_height; y++)
                mlx_put_pixel(game->img, x, y, CEILING_COLOR);
            continue;
        }
        
        float projected_height = (TILE_SIZE * screen_height) / ray->distance;
         
        // Fixed: Use screen_height instead of TILE_SIZE
        int wall_top = (int)((screen_height - projected_height) / 2);
        int wall_bottom = (int)((screen_height + projected_height) / 2);
         
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= screen_height) wall_bottom = screen_height - 1;
        
        uint32_t wall_color = ray->wasHitVertical ? WALL_COLOR_NR : WALL_COLOR_EW;
                 
        // Draw the vertical strip
        for (int y = 0; y < screen_height; y++) {
        uint32_t color;
        if (y < wall_top) {
            color = CEILING_COLOR;
        } else if (y >= wall_top && y <= wall_bottom) {
            color = wall_color;
        } else {
            color = FLOOR_COLOR;
        }
        // Add bounds check here!
        if (x >= 0 && x < game->win_width && y >= 0 && y < game->win_height)
            mlx_put_pixel(game->img, x, y, color);
    }
    }
}