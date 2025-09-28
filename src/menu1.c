/* This file compiles :
gcc -c src/menu1.c -o ofiles/menu1.o -IC:/msys64/ucrt64/include/SDL2
*/

#include "menu1.h"

void init_mapview(MapView* mapview){

}

void handle_eventsPausa(Game* game){
        while( SDL_PollEvent( &game->e ) ){ 
            if( game->e.type == SDL_QUIT )  
            game->running = 0;       
        }
}

int updatePausa(Game* game){
    return 0;
}

int renderPausa(Game* game){
    render_fondo(game, &game->pause->fondo);
    render_texto(game, &game->pause->pausa);
    return 0;
}

void init_Pausa(Game* game){
    init_TTF(&game->pause->pausa, "assets/comic.ttf");

    init_TTF(&game->pause->resume, "assets/comic.ttf");

    load_texto(game, &game->pause->pausa, 0, 0, 100 ,200);

    load_texto(game, &game->pause->resume, 0, 110, 100 ,400);

    create_image(&game->pause->fondo,"assets/monki.jpg");

    load_image(game, &game->pause->fondo, 50);
}

