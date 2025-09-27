#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gameloop.h"
#include "config.h"

typedef struct Game Game;

typedef struct Vector2D{
    int posX;
    int posY;
}Vector2D;

typedef struct Sprite{
    // init resources
    SDL_Surface* surface;
    SDL_Texture* texture;
    
    // display
    SDL_Rect src;
    SDL_Rect dest;
    
    // properties
    Vector2D position;
    char* nombre;
    float proportion;
    int monki_created;

    // movement
    int movingY;
    int movingX;

}Sprite;

int createSprite(Game* game, Sprite* monki, int x, int y, int src_w, int src_h, char* spriteName, char* filepath, float proportion);

int placeSprite(Game* game);

int updateSprite(Game* game);

void handle_eventsSprite(Game* game);

int renderSprite(Game* game);

void destroySprite(Sprite* monki);

void resizeSprite(Sprite* sprite);

void pickSprite(Game* game);

void clickSprite(Game* game);

#endif