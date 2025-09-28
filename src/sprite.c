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
    game->monki->dest.x = (WINDOW_W/2) - (game->monki->dest.w + (game->monki->dest.w)/2); 
    game->monki->dest.y = (WINDOW_H/2) + (game->monki->dest.h + (game->monki->dest.h)/2); // Spawn at center

    // Save where the monki is when spawned
    game->monki->position.posX = (WINDOW_W/2); 
    game->monki->position.posY = (WINDOW_H/2); 
    
    game->mouse.bpress = 0; // reset flag
    game->monki->monki_created = 1; // allows to spawn one texture per sprite

    printf("Sprite placed\n");
    SDL_Delay(200);
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
        //game->monki->position.distX = (abs(game->monki->position.posX - game->monki->dest.x));
        //game->monki->position.distY = (abs(game->monki->position.posY - game->monki->dest.y));
    if(game->monki->monki_created == 1 && game->mouse.bpress == 1){
        game->monki->position.posX = game->mouse.posm_x;
        game->monki->position.posY = game->mouse.posm_y;
    }
    checkMouse(game);
    clickSprite(game);
    resizeSprite(game->monki);
    return 0;
}

    // The function is only made for window height / 2, recalculate for another value
void resizeSprite(Sprite* sprite){
    // If going down -> get bigger
    if(sprite->dest.y >= WINDOW_H/2){ // Only changes size below WINDOW_HEIGHT
        sprite->proportion = (2.0f/225.0f)*(float)sprite->dest.y - (7.0f/3.0f); // Proportion as a function of Y_position
    }
    else    
        sprite->proportion = 1.0f/3.0f;
    sprite->dest.h = 46*3*(sprite->proportion);
    sprite->dest.w = 52*3*(sprite->proportion);
}

// Mouse over sprite flag check
void checkMouse(Game* game){ // Move sprite to mouse
    if(game->mouse.posm_x >= game->monki->dest.x 
    && game->mouse.posm_x < game->monki->dest.x + game->monki->dest.w
    && game->mouse.posm_y >= game->monki->dest.y 
    && game->mouse.posm_y < game->monki->dest.y + game->monki->dest.h
    ){
        game->monki->mouseOverSprite = 1;
    }
    else{ // Get mouse click if not
        game->monki->mouseOverSprite = 0;
    }
}

// Act upon sprite correpsoningly to checkMouse() flag
void clickSprite(Game* game){
    if(game->monki->mouseOverSprite == 1 && game->mouse.bpress == 1){
        game->monki->dest.x = game->mouse.posm_x - (game->monki->dest.w)/2;
        game->monki->dest.y = game->mouse.posm_y - (game->monki->dest.h)/2;
    }
    else if(game->mouse.bpress == 0){
        if(game->monki->position.posX - (game->monki->dest.x + (game->monki->dest.w)/2) != 0){
            // When difference is greater than 10
            if((game->monki->dest.x + (game->monki->dest.w)/2) < game->monki->position.posX){
                game->monki->dest.x += 500/60.0f;
            } else if((game->monki->dest.x + (game->monki->dest.w)/2) > game->monki->position.posX){
                game->monki->dest.x -= 500/60.0f;
            }
        }
        if(game->monki->position.posY - (game->monki->dest.y + (game->monki->dest.h)/2) != 0){
            if((game->monki->dest.y + (game->monki->dest.h)/2) < game->monki->position.posY){
                game->monki->dest.y += 500/60.0f;       
            } else if((game->monki->dest.y + (game->monki->dest.h)/2) > game->monki->position.posY){
                game->monki->dest.y -= 500/60.0f;
            }
        }
    }
}
// Distance
//(abs(game->monki->position.posX - game->monki->dest.x))
//(abs(game->monki->position.posY - game->monki->dest.y))

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


