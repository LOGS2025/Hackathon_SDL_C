/* This file compiles :
gcc -c src/gameloop.c -o ofiles/gameloop.o -IC:/msys64/ucrt64/include/SDL2
*/
/*
    Compile all:
gcc ofiles/framework.o ofiles/gameloop.o ofiles/menu1.o -o Monki.exe -LC:/msys64/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/
#include "gameloop.h"
#include "sprite.h"
#include "menu1.h"
#include "viewEvents.h"

int gameLoop(Game* game, GameState* gamestate){
    // Happen once
    game->pkeys = SDL_GetKeyboardState(NULL);

    SDL_SetRenderDrawColor(game->render, 255, 255, 255, 255);
    
    while( game->running == 1 ){

        SDL_RenderClear(game->render);

        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        
        SDL_Delay(20);
        
        if(game->pkeys[SDL_SCANCODE_M]){
            if(game->stateFlag == 0){
                game->current_state = &gamestate[1];
                game->stateFlag = 1;
            }
            else if(game->stateFlag == 1){
                game->current_state = &gamestate[0];
                game->stateFlag = 0;
            }
            SDL_Delay(100);
        }
        game->current_state->handle_events(game);
        game->current_state->update(game);
        game->current_state->render(game);

        SDL_RenderPresent(game->render);
    }
}

int close(Game* game){
    TTF_Quit();
    SDL_DestroyRenderer(game->render);
    SDL_DestroyWindow(game->ventana);
    SDL_Quit();
    return 0;
}

int init(Game* game, int win_h, int win_w){
    game->ventana = NULL;
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    //Window Width -> Window Height
    game->ventana = SDL_CreateWindow("{Game} Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        win_w, 
        win_h,
        0);
    if (!game->ventana)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    game->render= NULL;
    game->render = SDL_CreateRenderer(game->ventana, -1, render_flags);
    if (!game->render)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(game->ventana);
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() == -1) { // se inicializa la librería de SDL_ttf
    printf("error initializing TTF: %s\n", TTF_GetError());
    return 1;
    }           
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("IMG_Init failed: %s\n", IMG_GetError());
        return 1;
    }
    game->running = 1; // declare game running
    
    return 0;
}

int main(int argc, char* argv[]){

    Game game;

    Sprite monki = { .monki_created = 0, .dest.x = 0, .dest.y = 0};

    UI pause = {.pausa = {.msg = "Pausa"},.resume = {.msg = "Resumir"}};

    game.monki = &monki;
    game.pause = &pause;
    game.stateFlag = 0;

    int x = 80; // Origin from where to cut rect_src
    int y = 40;
    int w = 600 - x; // Dimensions of rect_src
    int h = 500 - y;
    
    printf("Created game and monito\n");
    
    
    GameState juegoState= { 
        .handle_events = handle_eventsSprite, 
        .update = updateSprite, 
        .render = renderSprite
    };

    GameState pausaState= { 
        .handle_events = handle_eventsPausa, 
        .update = updatePausa, 
        .render = renderPausa
    };
    
    GameState gamestates[] = {juegoState, pausaState};
    
    game.current_state = &juegoState;

    printf("Created gamestate\n");
    
    if(init(&game, 600,800)!=0)
        return 1;
    else
    {
        printf("Game running = %i\n", game.running); 

        createSprite(&game, game.monki, x,y, w, h, "Charly", 5, "assets/monki.jpg", h/10, w/10);
        
        init_Pausa(&game);

        gameLoop(&game, gamestates);
        
        destroySprite(game.monki);
        destroyFont(game.pause->pausa.font);
        destroyFont(game.pause->resume.font);
        
        close(&game);           
    }

    return 0;
}