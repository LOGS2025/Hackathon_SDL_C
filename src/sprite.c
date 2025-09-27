#include "sprite.h"
#include "config.h"
/* This file compiles :
gcc -c src/sprite.c -o ofiles/sprite.o -IC:/msys64/ucrt64/include/SDL2
*/

// Initializing function for any texture
int createSprite(Game* game, Sprite* monki, int x, int y, int src_w, int src_h, char* monkiName, char* filepath, float proportion){
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

    monki->proportion = 0;
    
    monki->dest.h = (46*proportion);
    monki->dest.w = (52*proportion);

    return 0;
}

// Once we created a monki, we need so be able to place it
int placeSprite(Game* game){
    if(game->e.type == SDL_MOUSEBUTTONDOWN){
        game->monki->dest.x = (WINDOW_W/2) - (game->monki->dest.w + (game->monki->dest.w)/2); 
        game->monki->dest.y = (WINDOW_H/2) + (game->monki->dest.h + (game->monki->dest.h)/2); // Spawn at center

        // Save where the monki is when spawned
        game->monki->position.posX = (WINDOW_W/2); 
        game->monki->position.posY = (WINDOW_H/2); 
        
        game->mouse.bpress = 0; // reset flag
        game->monki->monki_created = 1; // allows to spawn one texture per sprite

        printf("Sprite placed\n");
        SDL_Delay(200);
    }
    return 0;
}

// This function must have the logic to accept all the input it needs to execute actions
void handle_eventsSprite(Game* game){
    while( SDL_PollEvent( &game->e ) ){ 
        if( game->e.type == SDL_QUIT )  
        game->running = 0;       
        // Happpen conditionally
        if(game->monki->monki_created != 1)
            placeSprite(game);
        if(game->e.type == SDL_MOUSEBUTTONDOWN)
            game->mouse.bpress = 1; // button down!!!!
        if(game->e.type == SDL_MOUSEBUTTONUP)
            game->mouse.bpress = 0; // button up!         
    }   
}

// continuously update the monki!
int updateSprite(Game* game){
    if(game->monki->monki_created == 1 && game->mouse.bpress == 1){
        //pickSprite(game);
        game->monki->position.posX = game->mouse.posm_x;
        game->monki->position.posY = game->mouse.posm_y;
    }
    clickSprite(game);
    resizeSprite(game->monki);
    return 0;
}

void resizeSprite(Sprite* sprite){
    // If going down -> get bigger
    if(sprite->dest.y <= WINDOW_H){ // Only changes size below WINDOW_HEIGHT
        sprite->proportion = (2.0f/225.0f)*(float)sprite->dest.y - (7.0f/3.0f); // Proportion as a function of Y_position
    }
    else    
        sprite->proportion = 1;
    sprite->dest.h = 46*(sprite->proportion);
    sprite->dest.w = 52*(sprite->proportion);
}

// SPRITE IS PICKED UP BY MOUSE
void pickSprite(Game* game){
 if(game->mouse.posm_x >= game->monki->dest.x 
 && game->mouse.posm_x < game->monki->dest.x + 40
 && game->mouse.posm_y >= game->monki->dest.y 
 && game->mouse.posm_y < game->monki->dest.y + 40
    ){
        game->monki->dest.x = game->mouse.posm_x;
        game->monki->dest.y = game->mouse.posm_y;
    }
}

// SPRITE IS ONLY MOVING TO TOWARD THE CLICK
void clickSprite(Game* game){
    game->monki->movingX = 0;
    game->monki->movingY = 0;
    if(game->monki->position.posX - (game->monki->dest.x + (game->monki->dest.w)/2) != 0){
    // Move so the difference is set to zero
        if((game->monki->dest.x + (game->monki->dest.w)/2) < game->monki->position.posX){
            game->monki->dest.x += 2;
            game->monki->movingX = 1; // Moving right flag
        } else if((game->monki->dest.x + (game->monki->dest.w)/2) > game->monki->position.posX){
            game->monki->dest.x -= 2;
            game->monki->movingX = -1; // Moving left flag
        }
    if(game->monki->position.posY - (game->monki->dest.y + (game->monki->dest.h)/2) != 0)
        if((game->monki->dest.y + (game->monki->dest.h)/2) < game->monki->position.posY){
            game->monki->dest.y += 2;       
            game->monki->movingY = -1; // Moving down flag
        } else if((game->monki->dest.y + (game->monki->dest.h)/2) > game->monki->position.posY){
        //&& game->monki->dest.y > WINDOW_H/2){ // Restrict upward movement above te horizon line
            game->monki->dest.y -= 2;
            game->monki->movingY = 1; // Moving up flag
        }
    }
}
// Distance
//(int)((abs(game->monki->position.posX - game->monki->dest.x)))
//(int)((abs(game->monki->position.posY - game->monki->dest.y)))

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


