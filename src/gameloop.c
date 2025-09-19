#include "gameloop.h"
#include "framework.h"

int gameLoop(){
    Game game;
    createSprite();
    placeSprite();
    updateSprite();
    renderSprite();
    destroySprite();
}

int init_game(Game* game){
    game->ventana = SDL_CreateWindow("Jueguito",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1200,
    800,
    0)
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_CreateRenderer(game->ventana, -1, render_flags);
}

int main(int argc, char* argv[]){

}