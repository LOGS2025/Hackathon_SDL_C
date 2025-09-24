#include "framework.h"
/* This file compiles :
gcc -c src/framework.c -o ofiles/framework.o -IC:/msys64/ucrt64/include/SDL2
*/

// Initializing function for any texture
int createSprite(Game* game, Sprite* sprite, int x, int y, int src_w, int src_h, char* spriteName, int prop1, char* filepath, int dest_h, int dest_w){
    // Load the image into the surface
    sprite->surface = IMG_Load(filepath);
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
        printf("Mouse pressed!\n");
        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        sprite->dest.x = (game->mouse.posm_x); 
        sprite->dest.y = (game->mouse.posm_y); // spawn sprite at the position where the mouse clicked
        
        
        // Save where the sprite is when spawned
        sprite->position.posX = (game->mouse.posm_x); 
        sprite->position.posY = (game->mouse.posm_y); 
        
        game->mouse.bpress = 0; // reset flag
        sprite->monki_created = 1; // allows to spawn texture
    }
    return 0;
}

// This function goes inside handleEvents() and must have the logic to accept all the input it needs to execute actions
void moveSprite(Game* game, Sprite* sprite){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        game->mouse.bpress = 1; // button down!!!!
    }
    if(game->e.type == SDL_MOUSEBUTTONUP)
    game->mouse.bpress = 0; // button up!
}

void handle_eventsSprite(Game* game, Sprite* sprite){
        while( SDL_PollEvent( &game->e ) ){ 
            if( game->e.type == SDL_QUIT )  
            game->running = 0;       
            // Happpen conditionally
            if(game->pkeys[SDL_SCANCODE_1] && sprite->monki_created == 0){ // Only works once
                game->mouse.bpress = 1;
            }
            if(game->mouse.bpress==1 && sprite->monki_created == 0){
                placeSprite(game, sprite);
            }
            moveSprite(game, sprite);            
        } 
}

// continuously update the sprite!
int updateSprite(Game* game, Sprite* sprite){
    if(sprite->monki_created == 1){
        // Get the distance between the mouse click and the sprite
        if(game->mouse.bpress == 1
            && game->mouse.posm_x >= sprite->dest.x 
        && game->mouse.posm_x < sprite->dest.x + 40
        && game->mouse.posm_y >= sprite->dest.y 
        && game->mouse.posm_y < sprite->dest.y + 40
    ){
        sprite->dest.x = game->mouse.posm_x;
            sprite->dest.y = game->mouse.posm_y;
        }
        else if(game->mouse.bpress == 1){
        sprite->position.posX = game->mouse.posm_x;
        sprite->position.posY = game->mouse.posm_y;
        }
        if(sprite->position.posX - sprite->dest.x != 0)
        // Move so the difference is set to zero
            if(sprite->dest.x < sprite->position.posX)
                sprite->dest.x += (int)((abs(sprite->position.posX - sprite->dest.x)))
    ;
            else if(sprite->dest.x > sprite->position.posX)
                sprite->dest.x -= (int)((abs(sprite->position.posX - sprite->dest.x)));
                
        if(sprite->position.posY - sprite->dest.y != 0)
            if(sprite->dest.y < sprite->position.posY) 
                sprite->dest.y += (int)((abs(sprite->position.posY - sprite->dest.y)));
            else if(sprite->dest.y > sprite->position.posY)
                sprite->dest.y -= (int)((abs(sprite->position.posY - sprite->dest.y)));
        return 0;
    }
}

int renderSprite(Game* game, Sprite* sprite){
    if(sprite->monki_created == 1){
    if(SDL_RenderCopy(game->render, sprite->texture, &sprite->src, &sprite->dest)!=0)
    printf("Couldnt render copy\n");
    }
    return 0;
}

void destroySprite(Sprite* sprite){
    SDL_DestroyTexture(sprite->texture);
}