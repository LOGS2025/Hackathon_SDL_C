#include "sprite.h"
/* This file compiles :
gcc -c src/monki.c -o ofiles/monki.o -IC:/msys64/ucrt64/include/SDL2
*/

// Initializing function for any texture
int createSprite(Game* game, Sprite* monki, int x, int y, int src_w, int src_h, char* monkiName, int prop1, char* filepath, int dest_h, int dest_w){
    // Load the image into the surface
    monki->surface = IMG_Load(filepath);
    if(!monki->surface){
        printf("Error loading monki surface\n");
        return 1;
    } 
    // Load the surface into the texture with the renderer
    monki->texture = SDL_CreateTextureFromSurface(game->render, monki->surface);
    if(!monki->texture){
        printf("Error creating texture for monki\n");
        return 1;
    } 
    // Free the surface, the texture gets destroyed with another function
    SDL_FreeSurface(monki->surface);

    // Set the part of the image we need to copy
    monki->src.h = src_h;
    monki->src.w = src_w;
    monki->src.x = x;
    monki->src.y = y;
    
    monki->dest.h = dest_h;
    monki->dest.w = dest_w; // Get parameters
    return 0;
}

// Once we created a monki, we need so be able to place it
int placeSprite(Game* game){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        printf("Mouse pressed!\n");
        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        game->monki->dest.x = (game->mouse.posm_x); 
        game->monki->dest.y = (game->mouse.posm_y); // spawn monki at the position where the mouse clicked
        
        
        // Save where the monki is when spawned
        game->monki->position.posX = (game->mouse.posm_x); 
        game->monki->position.posY = (game->mouse.posm_y); 
        
        game->mouse.bpress = 0; // reset flag
        game->monki->monki_created = 1; // allows to spawn texture
        SDL_Delay(200);
    }
    return 0;
}

// This function goes inside handleEvents() and must have the logic to accept all the input it needs to execute actions
void moveSprite(Game* game){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        game->mouse.bpress = 1; // button down!!!!
    }
    if(game->e.type == SDL_MOUSEBUTTONUP)
    game->mouse.bpress = 0; // button up!
}

void handle_eventsSprite(Game* game){
    while( SDL_PollEvent( &game->e ) ){ 
        if( game->e.type == SDL_QUIT )  
        game->running = 0;       
        // Happpen conditionally
        if(game->pkeys[SDL_SCANCODE_1] && game->monki->monki_created == 0){ // Only works once
            game->mouse.bpress = 1;
        }
        if(game->mouse.bpress==1 && game->monki->monki_created == 0){
            placeSprite(game);
        }
        moveSprite(game);            
    } 
}

// continuously update the monki!
int updateSprite(Game* game){
    if(game->monki->monki_created == 1){
        // Get the distance between the mouse click and the monki
        if(game->mouse.bpress == 1
            && game->mouse.posm_x >= game->monki->dest.x 
        && game->mouse.posm_x < game->monki->dest.x + 40
        && game->mouse.posm_y >= game->monki->dest.y 
        && game->mouse.posm_y < game->monki->dest.y + 40
    ){
        game->monki->dest.x = game->mouse.posm_x;
            game->monki->dest.y = game->mouse.posm_y;
        }
        else if(game->mouse.bpress == 1){
        game->monki->position.posX = game->mouse.posm_x;
        game->monki->position.posY = game->mouse.posm_y;
        }
        if(game->monki->position.posX - game->monki->dest.x != 0){
        // Move so the difference is set to zero
            if(game->monki->dest.x < game->monki->position.posX)
                game->monki->dest.x += (int)((abs(game->monki->position.posX - game->monki->dest.x)));
            else if(game->monki->dest.x > game->monki->position.posX)
                game->monki->dest.x -= (int)((abs(game->monki->position.posX - game->monki->dest.x)));
   
        if(game->monki->position.posY - game->monki->dest.y != 0)
            if(game->monki->dest.y < game->monki->position.posY) 
                game->monki->dest.y += (int)((abs(game->monki->position.posY - game->monki->dest.y)));
            else if(game->monki->dest.y > game->monki->position.posY)
                game->monki->dest.y -= (int)((abs(game->monki->position.posY - game->monki->dest.y)));
        }
    }
    return 0;
}

int renderSprite(Game* game){
    if(game->monki->monki_created == 1){
    if(SDL_RenderCopy(game->render, game->monki->texture, &game->monki->src, &game->monki->dest)!=0)
    printf("Couldnt render copy\n");
    }
    return 0;
}

void destroySprite(Sprite* monki){
    SDL_DestroyTexture(monki->texture);
}


