#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gameloop.h"

typedef struct Game Game;

typedef struct Vector2D{
    int posX;
    int posY;
}Vector2D;

typedef struct Sprite{
    SDL_Surface* surface;
    SDL_Texture* texture;
    
    SDL_Rect src;
    SDL_Rect dest;
    
    Vector2D position;
    char* nombre;
    int prop1;
    int monki_created;
    
}Sprite;

int createSprite(Game* game, Sprite* monki, int x, int y, int src_w, int src_h, char* spriteName, int prop1, char* filepath, int dest_h, int dest_w);

int placeSprite(Game* game);

void moveSprite(Game* game);

int updateSprite(Game* game);

void handle_eventsSprite(Game* game);

int renderSprite(Game* game);

void destroySprite(Sprite* monki);


#endif