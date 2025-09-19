#include "framework.h"

// Initializing function for any texture
int createSprite(Game* game, Sprite* sprite, 
    int x, int y, int src_w, int src_h, char* spriteName, 
    int prop1 /* , Filepath*/, int dest_h, int dest_w){
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
    sprite->src.h = src_h;
    sprite->src.w = src_w;
    sprite->src.x = x;
    sprite->src.y = y;
    
    sprite->dest.h = dest_h;
    sprite->dest.w = dest_w; // Get parameters
    return 0;
}

// Once we created a sprite, we need so be able to place it
int placeSprite(Game* game, Sprite* sprite){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        sprite->dest.x = (game->mouse.posm_x); 
        sprite->dest.y = (game->mouse.posm_y); // spawn sprite at the position where the mouse clicked
        
        
        // Save where the sprite is when spawned
        sprite->position.posX = (game->mouse.posm_x); 
        sprite->position.posY = (game->mouse.posm_y); 

        // We copy it for the render to do the work
        SDL_RenderCopy(game->render, sprite->texture, &sprite->src, &sprite->dest);
    }
    return 0;
}

// This function goes inside handleEvents() and must have the logic to accept all the input it needs to execute actions
int updateSprite(Game* game, Sprite* sprite){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        int x = (game->mouse.posm_x); // where mouse is ON OUR WINDOW, not on the game surface!
        int y = (game->mouse.posm_y); // where mouse is ON OUR WINDOW, not on the game surface!!!!!!!
    }
    sprite->dest.x = game->mouse.posm_x;
    sprite->dest.y = game->mouse.posm_y;
    return 0;
}

int renderSprite(Game* game){
    SDL_RenderPresent(game->render);
}

void destroySprite(Sprite* sprite){
    SDL_DestroyTexture(sprite->texture);
}