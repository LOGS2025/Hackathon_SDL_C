#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Game{
    SDL_Renderer* render;
    SDL_Window* ventana;
    SDL_Event e;

    Mouse mouse;

    int running;

}Game;

typedef struct Sprite{
    SDL_Surface* surface;
    SDL_Texture* texture;
    
    SDL_Rect src;
    SDL_Rect dest;

    Vector2D position;
    char* nombre;
    int prop1;
}Sprite;

typedef struct Vector2D{
    int posX;
    int posY;
}Vector2D;

typedef struct Mouse{
    int posm_x;
    int posm_y;

}Mouse;

int createSprite(Game* game, Sprite* sprite, int x, int y, int src_w, int src_h, char* spriteName, int prop1, char* filepath, int dest_h, int dest_w);

int placeSprite(Game* game, Sprite* sprite);

int updateSprite(Game* game, Sprite* sprite);

int renderSprite(Game* game);

void destroySprite(Sprite* sprite);


#endif