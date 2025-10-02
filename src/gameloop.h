#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "sprite.h"
#include "menu1.h"
#include "geometry.h"

typedef struct UI UI;
typedef struct Sprite Sprite;
typedef struct DrawElement DrawElement;

typedef struct Mouse{
    int posm_x;
    int posm_y;
    int bpress;
}Mouse;

typedef struct Game Game;

typedef struct GameState{
    void (*handle_events)(struct Game*);
    int (*update)(struct Game*);
    int (*render)(struct Game*);
}GameState;

typedef struct Game{
    SDL_Renderer* render;
    SDL_Window* ventana;
    SDL_Event e;
    
    Mouse mouse;
    
    int running;
    int stateFlag;
    
    const Uint8* pkeys;

    // Game playState structs
    Sprite* monki;

    // Game pauseState struct
    UI* pause;
    UI* mapa;
    
    DrawElement* drawList;  // Lista de elementos dibujados
    int isDrawing;          // Flag si estamos dibujando
    int drawType;           // Tipo de dibujo actual
    int drawFilled;         // Relleno o contorno
    SDL_Color drawColor;

    GameState* current_state;
    GameState* gamestates;
}Game;

int gameLoop(Game* game, GameState gamestates[]);

int close(Game* game);

int init(Game* game, int win_h, int win_w);


#endif