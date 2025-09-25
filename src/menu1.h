#ifndef MENU1_H
#define MENU1_H

#include "SDL2/SDL_ttf.h"
#include "sprite.h"
#include "gameloop.h"

typedef struct Game Game;

typedef struct Texto{
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;
    char str_buffer[60];
    char str_num[10];
    char* msg;
    TTF_Font* font;
}Texto;

typedef struct Tilemap{

}Tilemap;

typedef struct Imagen{
    SDL_Texture* texture;
    SDL_Surface* surface;
    char* filepath;
    SDL_Rect src_rect;
}Imagen;

typedef struct UI{
    Texto pausa;
    Texto otra_cosa;
    Texto salir;
    Texto resume;
    Imagen fondo;
}UI;

typedef struct MapView{
    Tilemap tilemap;
    UI ui_1;
}MapView;

int load_texto(Game* game, Texto* texto, int x, int y, int h, int w);

void create_image(Imagen* image, char* filepath);

int init_TTF(Texto* texto, char* filepath);

int load_image(Game* game, Imagen* image, int transparency);

int render_fondo(Game* game, Imagen* image);

int render_texto(Game* game, Texto* texto);

int renderPausa(Game* game);

int updatePausa(Game* game);

void handle_eventsPausa(Game* game);

void init_Pausa(Game* game);

void destroyFont(TTF_Font* font);

#endif