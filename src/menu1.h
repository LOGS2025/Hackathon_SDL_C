#ifndef MENU1_H
#define MENU1_H

#include "SDL2/SDL_ttf.h"
#include "sprite.h"
#include "gameloop.h"
#include "text.h"

typedef struct Game Game;
typedef struct Texto Texto;
typedef struct Imagen Imagen;



typedef struct Tilemap{

}Tilemap;

typedef struct UI{
    Texto* pausa;
    Texto* otra_cosa;
    Texto* salir;
    Texto* resume;
    Imagen* fondo;
}UI;

typedef struct MapView{
    Tilemap tilemap;
    UI ui_1;
}MapView;

int renderPausa(Game* game);

int updatePausa(Game* game);

void handle_eventsPausa(Game* game);

void init_Pausa(Game* game);


#endif