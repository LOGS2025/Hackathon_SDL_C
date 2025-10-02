#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "gameloop.h"


#define MAX_POINTS 10

typedef struct Game Game;

typedef struct DrawElement {
    int type;           // 0: línea, 1: rectángulo, 2: círculo
    SDL_Point points[2]; // Solo necesitamos 2 puntos para estas formas
    SDL_Color color;
    int filled;
    struct DrawElement* next;
} DrawElement;

void handle_eventsDraw(Game* game);

int updateDraw(Game* game);

int renderDraw(Game* game);

void destroyDraw(Game* game);

void eraseDraw(Game* game);

void setDrawColor(Game* game, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void setDrawType(Game* game, int type);

void toggleDrawFilled(Game* game);

#endif