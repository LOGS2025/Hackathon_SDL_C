// Initializing function for any texture
int createSprite(Game* game, Sprite* sprite, int x, int y, int w, int h, char* spriteName, int prop1 /* , Filepath*/){
    // Load the image into the surface
    sprite->surface = IMG_Load("");
    if(!sprite->surface){
        printf("Error loading sprite surface\n");
        return 1;
    } 
    // Load the surface into the texture with the renderer
    sprite->texture = SDL_CreateTextureFromSurface(game->render, sprite->surface);
    if(!sprite->texture){
        printf("Error creating texture for sprite\n");
        return 1;
    } 
    // Free the surface, the texture gets destroyed with another function
    SDL_FreeSurface(sprite->surface);

    // Set the part of the image we need to copy
    sprite->src.h = h;
    sprite->src.w = w;
    sprite->src.x = x;
    sprite->src.y = y;

    // init other properties
    sprite->sprite_name = spriteName;

    sprite->property_1 = prop1;

    return 0;
}

// Once we created a sprite, we need so be able to place it
int placeSprite(Game* game, Sprite* sprite, int h, int w){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        sprite->Dest.x = (game->mouse.posm_x)/TILE_DEST_SIZE; 
        sprite->Dest.y = (game->mouse.posm_y)/TILE_DEST_SIZE; // spawn sprite at the position where the mouse clicked
        
        sprite->Dest.h = h;
        sprite->Dest.w = w; // Get parameters
        
        // Save where the sprite is when spawned
        sprite->position.x = (game->mouse.posm_x)/TILE_DEST_SIZE; 
        sprite->position.y = (game->mouse.posm_y)/TILE_DEST_SIZE; 

        // We copy it for the render to do the work
        SDL_RenderCopy(game->render, sprite->texture, &sprite->src, &sprite->Dest);
    }
    return 0;
}

// This function goes inside handleEvents() and must have the logic to accept all the input it needs to execute actions
int updateSprite(Game* game, Sprite* sprite){
    if(game->e.type == SDL_MOUSEBUTTONUP){
        game->mouse.mouse_down = false;
    }   
    while(game->e.type == SDL_MOUSEBUTTONDOWN){
        if(){
            SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        }
        int x = (game->mouse.posm_x)/TILE_DEST_SIZE; // where mouse is ON OUR WINDOW, not on the game surface!
        int y = (game->mouse.posm_y)/TILE_DEST_SIZE; // where mouse is ON OUR WINDOW, not on the game surface!!!!!!!
        game->mouse.mouse_down = true; // maybe these flags are not needed for these loop but must check with other functions
    }
}       

int renderSprite(){

}

void destroySprite(){

}