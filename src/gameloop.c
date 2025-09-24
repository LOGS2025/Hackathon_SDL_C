/* This file compiles :
gcc -c src/gameloop.c -o ofiles/gameloop.o -IC:/msys64/ucrt64/include/SDL2
*/
/*
    Compile all:
gcc ofiles/framework.o ofiles/gameloop.o ofiles/menu1.o -o Monki.exe -LC:/msys64/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/
#include "gameloop.h"
#include "framework.h"
#include "menu1.h"

int gameLoop(Game* game, Sprite* sprite, UI* ui){
    // Happen once
    game->pkeys = SDL_GetKeyboardState(NULL);

    //SDL_SetRenderDrawColor(game->render, 255, 255, 255, 255);

    SDL_RenderPresent(game->render);

    while( game->running == 1 ){

        SDL_RenderClear(game->render);

        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);
        
        SDL_Delay(20);
        
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
        // Always happens
        if(sprite->monki_created == 1){
            updateSprite(game, sprite);
            renderSprite(game, sprite);
        }

        render_fondo(game, &ui->fondo);
        render_texto(game, &ui->pausa);
        render_texto(game, &ui->resume);

        SDL_RenderPresent(game->render);
    }
}

int gameMenu(Game* game, UI* ui){
    while( game->running == 1 ){ 
        SDL_RenderClear(game->render);

        SDL_GetMouseState(&game->mouse.posm_x,&game->mouse.posm_y);

        SDL_Delay(20);
        
        while( SDL_PollEvent( &game->e ) ){ 
            if( game->e.type == SDL_QUIT )  
            game->running = 0;             
        } 

        render_fondo(game, &ui->fondo);
        render_texto(game, &ui->pausa);

        SDL_RenderPresent(game->render);
    }
    return 0;
}

int close(Game* game)
{
    //TTF_CloseFont(game->font);
    //TTF_Quit();
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
    Sprite monito = {.monki_created = 0, .dest.x = 0, .dest.y = 0};
    UI ui_1 = {.pausa = {.msg = "Pausa"},.resume = {.msg = "Resumir"}};

    int x = 80; // Origin from where to cut rect_src
    int y = 40;
    int w = 600 - x; // Dimensions of rect_src
    int h = 500 - y;

    init(&game, 600,800);
    printf("Game running = %i\n", game.running);

    init_TTF(&ui_1.pausa, "assets/comic.ttf");

    init_TTF(&ui_1.resume, "assets/comic.ttf");

    load_texto(&game, &ui_1.pausa, 0, 0, 100 ,200);

    load_texto(&game, &ui_1.resume, 0, 110, 100 ,400);

    create_image(&ui_1.fondo,"assets/monki.jpg");

    load_image(&game, &ui_1.fondo, 50);
    
    // Happen once
    game.pkeys = SDL_GetKeyboardState(NULL);
    
    //SDL_SetRenderDrawColor(game->render, 255, 255, 255, 255);
    
    createSprite(&game, &monito, x,y, w, h, "Charly", 5, "assets/monki.jpg", h/10, w/10);
    
    gameLoop(&game, &monito, &ui_1);
    
    destroySprite(&monito);
    
    close(&game);           

    return 0;
}