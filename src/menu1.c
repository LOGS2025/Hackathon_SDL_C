/* This file compiles :
gcc -c src/menu1.c -o ofiles/menu1.o -IC:/msys64/ucrt64/include/SDL2
*/

#include "menu1.h"

void init_mapview(MapView* mapview){

}

int init_TTF(Texto* texto, char* filepath){
    //this opens a font style and sets a size
    texto->font = TTF_OpenFont(filepath, 32);
    if (!texto->font){
        printf("Error opening font: %s\n", TTF_GetError());
        return 1;
    }
    return 0;
}

int load_texto(Game* game, Texto* texto, int x, int y, int h, int w){
// Elegimos el color del texto
    // or do MapRGB()
    texto->color.a = 0;
    texto->color.b = 0;
    texto->color.g = 0;
    texto->color.r = 0; // Negro

    //if(sprintf(texto->str_num, "%d", 10)<0) 
    //    printf("Failed concatenating strings\n"); 
    strcpy(texto->str_buffer, texto->msg);
    //strcat(texto->str_buffer,texto->str_num);

    texto->surface = TTF_RenderText_Solid(texto->font, texto->str_buffer, texto->color);
    if(!texto->surface) return 1;

    texto->texture = SDL_CreateTextureFromSurface(game->render, texto->surface);
    if(!texto->texture) return 1;
    
    SDL_FreeSurface(texto->surface);

    //Añadimos el rectángulo sobre el que se va a mostrar el texto
    texto->rect.h = h;
    texto->rect.w = w;
    texto->rect.x = x;
    texto->rect.y = y;
    return 0;
}       

void create_image(Imagen* image, char* filepath){
    image->filepath = filepath;
}

/* Loads image to surface -> to texture. The image isn't loaded into a Rect because it
    may be used for a Sprite, a background or something else.*/
int load_image(Game* game, Imagen* image, int transparency){
// Load the image into the surface
    image->surface = IMG_Load(image->filepath);
    if(!image->surface){
        printf("Error loading image surface\n");
        return 1;
    }     
    // Load the surface into the texture with the renderer
    image->texture = SDL_CreateTextureFromSurface(game->render, image->surface);
    if(!image->texture){
        printf("Error creating texture for image\n");
        return 1;
    } 
        // enable alpha blending
    SDL_SetTextureBlendMode(image->texture, SDL_BLENDMODE_BLEND);

    // set alpha (0 = fully transparent, 255 = fully opaque)
    SDL_SetTextureAlphaMod(image->texture, (transparency*250)/100); // 50% transparency
    // Free the surface, the texture gets destroyed with another function
    SDL_FreeSurface(image->surface);
    return 0;
}

int render_fondo(Game* game, Imagen* image){  
    if(SDL_RenderCopy(game->render, image->texture, NULL, NULL)!=0)
        return 1;
    return 0;
}

int render_texto(Game* game, Texto* texto){
    if(SDL_RenderCopy(game->render, texto->texture,NULL, &texto->rect)!=0)
        return 1;
    return 0;
}


