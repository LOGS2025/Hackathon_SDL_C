#ifndef MENU1_H
#define MENU1_H

#include "framework.h"

typedef struct Texto{
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
}Texto;

typedef struct Tilemap{

}Tilemap;

typedef struct Fondo{
    SDL_Texture* texture;
    SDL_Surface* surface;
    char* filepath;
}Fondo;

typedef struct UI{
    Texto pausa;
    Texto otra_cosa;
    Texto salir;
    Texto resume;
    Fondo fondo;
}UI;

typedef struct MapView{
    Tilemap tilemap;
    UI ui_1;
}MapView;

#endif