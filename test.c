/*

void castRay(t_game *game, float rayAngle, int stripId){
    rayAngle = normalizeAngle(rayAngle);
    
    int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < M_PI / 2 || rayAngle > 3 * M_PI / 2; 
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    // HORIZONTAL RAY CASTING
    int foundHorizontalWallHit = 0;
    float horizWallHitX = 0;
    float horizWallHitY = 0;
    
    // Find y-coordinate of closest horizontal grid intersection
    yintercept = floor(game->player.player_y / game->mini_map_tile) * game->mini_map_tile;
    yintercept += isRayFacingDown ? game->mini_map_tile : 0;
    
    // Find x-coordinate
    if (fabs(tan(rayAngle)) < 0.001) {
        xintercept = game->player.player_x;
        xstep = 0;
    } else {
        xintercept = game->player.player_x + (yintercept - game->player.player_y) / tan(rayAngle);
        xstep = game->mini_map_tile / tan(rayAngle);
        xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
        xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
    }

    ystep = game->mini_map_tile;
    ystep *= isRayFacingUp ? -1 : 1;

    float nextHorizTouchX = xintercept; 
    float nextHorizTouchY = yintercept;

    // FIXED: Correct boundary checking with pixel coordinates
    int maxPixelX = game->m_width * game->mini_map_tile;
    int maxPixelY = game->m_height * game->mini_map_tile;

    while (nextHorizTouchX >= 0 && nextHorizTouchX < maxPixelX && 
           nextHorizTouchY >= 0 && nextHorizTouchY < maxPixelY) {
        
        // FIXED: Correct collision checking
        float xToCheck = nextHorizTouchX;
        float yToCheck = nextHorizTouchY;
        
        // Adjust for direction - check the tile we're actually entering
        if (isRayFacingUp) {
            yToCheck -= 1;  // Check tile above the intersection
        }
        
        if (check_for_collision(game, xToCheck, yToCheck)) {
            horizWallHitX = nextHorizTouchX;
            horizWallHitY = nextHorizTouchY;
            foundHorizontalWallHit = 1;
            break;
        }
        
        if (xstep == 0) break; // Prevent infinite loop
        nextHorizTouchX += xstep;
        nextHorizTouchY += ystep;
    }

    // VERTICAL RAY CASTING
    int foundVertWallHit = 0;
    float wallVertHitX = 0;
    float wallVertHitY = 0;

    // Find x-coordinate of closest vertical grid intersection
    xintercept = floor(game->player.player_x / game->mini_map_tile) * game->mini_map_tile;
    xintercept += isRayFacingRight ? game->mini_map_tile : 0;

    // Find y-coordinate
    if (fabs(cos(rayAngle)) < 0.001) {
        yintercept = game->player.player_y;
        ystep = 0;
    } else {
        yintercept = game->player.player_y + (xintercept - game->player.player_x) * tan(rayAngle);
        ystep = game->mini_map_tile * tan(rayAngle);
        ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
        ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
    }

    xstep = game->mini_map_tile;
    xstep *= isRayFacingLeft ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    while (nextVertTouchX >= 0 && nextVertTouchX < maxPixelX && 
           nextVertTouchY >= 0 && nextVertTouchY < maxPixelY) {
        
        // FIXED: Correct collision checking
        float xToCheck = nextVertTouchX;
        float yToCheck = nextVertTouchY;
        
        // Adjust for direction - check the tile we're actually entering
        if (isRayFacingLeft) {
            xToCheck -= 1;  // Check tile to the left of the intersection
        }
        
        if (check_for_collision(game, xToCheck, yToCheck)) {
            foundVertWallHit = 1;
            wallVertHitX = nextVertTouchX;
            wallVertHitY = nextVertTouchY;
            break;
        }
        
        if (ystep == 0) break; // Prevent infinite loop
        nextVertTouchX += xstep;
        nextVertTouchY += ystep;
    }

    // Calculate distances and choose closest hit
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

    game->ray[stripId].rayAngle = rayAngle;
    game->ray[stripId].isRayFacingDown = isRayFacingDown;
    game->ray[stripId].isRayFacingUp = isRayFacingUp;
    game->ray[stripId].isRayFacingLeft = isRayFacingLeft;
    game->ray[stripId].isRayFacingRight = isRayFacingRight;
}
*/