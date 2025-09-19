#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL2/SDL.h>

#include "framework.h"

typedef struct Game Game;

typedef struct Vector2D Vector2D;

typedef struct Mouse Mouse;

int gameLoop(Game* game, Sprite* sprite);

int close(Game* game);

int init(Game* game, int win_h, int win_w);

#endif