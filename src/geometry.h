#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "menu1.h"


#define MAX_POINTS 10

/* void init_Draw(Game* game) {
    // Inicializar sistema de dibujo si no está inicializado
    if(game->drawList == NULL) {
        game->drawList = NULL;
        game->isDrawing = 0;
        game->drawType = 1; // Rectángulo por defecto
        game->drawFilled = 0;
        game->drawColor = (SDL_Color){255, 0, 0, 255};
    }
}*/


void handle_eventsDraw(Game* game);
int updateDraw(Game* game);
int renderDraw(Game* game);
void destroyDraw(Game* game);

void eraseDraw(Game* game);
void setDrawColor(Game* game, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void setDrawType(Game* game, int type);
void toggleDrawFilled(Game* game);

#endif