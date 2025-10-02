/*
Depending on our view setup we need a different system. 
In case of an isometric view, or a bird view. 

The aim of these file is to provide a geometric function foundation for
more complex drawings like boxes, poligons, and more symbolic drawings like 
ventilation, pumps, etc.

This objects should be made with malloc since we don't know how many there will be? 
Maybe?

This file compiles
*/

#include "geometry.h"


void handle_eventsDraw(Game* game){
  
    while(SDL_PollEvent(&game->e)) {
            if(game->e.type == SDL_QUIT) {
                game->running = 0;
            }
            
            if(game->e.type == SDL_MOUSEBUTTONDOWN) {
                    game->isDrawing = 1;
                    
                    // Crear nuevo elemento temporal
                    DrawElement* newElement = (DrawElement*)malloc(sizeof(DrawElement));
                    newElement->type = game->drawType;
                    newElement->points[0].x = game->mouse.posm_x;
                    newElement->points[0].y = game->mouse.posm_y;
                    newElement->points[1] = newElement->points[0]; // Inicializar segundo punto
                    newElement->color = game->drawColor;
                    newElement->filled = game->drawFilled;
                    newElement->next = NULL;
                    
                    // Agregar a la lista
                    if(game->drawList == NULL) {
                        game->drawList = newElement;
                    } else {
                        // Agregar al final de la lista
                        DrawElement* current = game->drawList;
                        while(current->next != NULL) {
                            current = current->next;
                        }
                        current->next = newElement;
                    }
            }
            
            if(game->e.type == SDL_MOUSEBUTTONUP && game->isDrawing) {
                    game->isDrawing = 0;
            }
            if(game->e.type == SDL_MOUSEMOTION && game->isDrawing) {
                // Actualizar el último elemento de la lista
                DrawElement* current = game->drawList;
                while(current->next != NULL) {
                    current = current->next;
                }
                current->points[1].x = game->mouse.posm_x;
                current->points[1].y = game->mouse.posm_y;
            }
            
            if(game->e.type == SDL_KEYDOWN) {
                switch(game->e.key.keysym.sym) {
                    case SDLK_1: 
                        setDrawType(game, 0);
                        printf("Caso1\n"); 
                        break; // Línea
                    case SDLK_2: 
                        setDrawType(game, 1); 
                        break; //Rectángulo
                    case SDLK_3: 
                        setDrawType(game, 2); 
                        break; // Círculo
                    case SDLK_f: 
                        toggleDrawFilled(game); 
                        break;
                    case SDLK_c: // Cambiar color aleatorio
                        setDrawColor(game, rand() % 256, rand() % 256, rand() % 256, 255);
                        break;
                    case SDLK_e: // Borrar todo
                        eraseDraw(game);
                        break;
                }
            }
        }
}    


int updateDraw(Game* game){

}

int renderDraw(Game* game){
    SDL_SetRenderDrawColor(game->render, 240, 240, 240, 255);
    SDL_RenderClear(game->render);
    
    // Instrucciones en la parte superior
    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);

    DrawElement* current = game->drawList;
     while(SDL_PollEvent(&game->e)) {
        if(game->e.type == SDL_QUIT) {
            game->running = 0;
        }
        
        if(game->e.type == SDL_KEYDOWN) {
            if(game->e.key.keysym.sym == SDLK_ESCAPE) {
                // Volver al estado anterior (juego)
                game->current_state = &game->gamestates[0];
                SDL_Delay(100);
            }
        }

    while(current != NULL) {
        SDL_SetRenderDrawColor(game->render, 
                              current->color.r, 
                              current->color.g, 
                              current->color.b, 
                              current->color.a);
        
        switch(current->type) {
            case 0: // Línea
                SDL_RenderDrawLine(game->render, 
                                 current->points[0].x, 
                                 current->points[0].y,
                                 current->points[1].x, 
                                 current->points[1].y);
                break;
                
            case 1: // Rectángulo
                {
                    SDL_Rect rect = {
                        current->points[0].x < current->points[1].x ? current->points[0].x : current->points[1].x,
                        current->points[0].y < current->points[1].y ? current->points[0].y : current->points[1].y,
                        abs(current->points[1].x - current->points[0].x),
                        abs(current->points[1].y - current->points[0].y)
                    };
                    
                    if(current->filled) {
                        SDL_RenderFillRect(game->render, &rect);
                           printf("DEBUG: Dibujando rectángulo en (%d,%d) tamaño %dx%d\n");
                    } else {
                        SDL_RenderDrawRect(game->render, &rect);
                           printf("DEBUG: Dibujando rectángulo en (%d,%d) tamaño %dx%d\n");
                    }
                }
                break;
                
            case 2: // Círculo
                {
                    int centerX = current->points[0].x;
                    int centerY = current->points[0].y;
                    int radius = (int)sqrt(pow(current->points[1].x - centerX, 2) + 
                                          pow(current->points[1].y - centerY, 2));
                    
                    // Dibujar círculo - versión simple
                    for(int angle = 0; angle < 360; angle += 2) {
                        float rad = angle * M_PI / 180.0f;
                        int x = centerX + radius * cos(rad);
                        int y = centerY + radius * sin(rad);
                        SDL_RenderDrawPoint(game->render, x, y);
                    }
                    
                    // Relleno
                    if(current->filled) {
                        for(int r = 1; r < radius; r++) {
                            for(int angle = 0; angle < 360; angle += 3) {
                                float rad = angle * M_PI / 180.0f;
                                int x = centerX + r * cos(rad);
                                int y = centerY + r * sin(rad);
                                SDL_RenderDrawPoint(game->render, x, y);
                            }
                        }
                    }
                }
                break;
        }
        
        current = current->next;
    }
}}

void destroyDraw(Game* game) {
    eraseDraw(game); // Llama a erase para limpiar toda la lista
}

void eraseDraw(Game* game) {
    DrawElement* current = game->drawList;
    while(current != NULL) {
        DrawElement* next = current->next;
        free(current);
        current = next;
    }
    game->drawList = NULL;
    game->isDrawing = 0;
}

void setDrawColor(Game* game, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    game->drawColor.r = r;
    game->drawColor.g = g;
    game->drawColor.b = b;
    game->drawColor.a = a;
}

void setDrawType(Game* game, int type) {
    game->drawType = type;
}

void toggleDrawFilled(Game* game) {
    game->drawFilled = !game->drawFilled;
}