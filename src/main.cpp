#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <thread>
#define SDL_MAIN_HANDLED


void SDL_ExitWithError(const char *string);

#include <SDL.h>
#include "carte.h"
#include "player.h"
#include <fstream>

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
    if(t != NULL){
        SDL_DestroyTexture((t));
    }
    if(r != NULL){
        SDL_DestroyRenderer(r);
    }
    if(w != NULL){
        SDL_DestroyWindow(w);
    }
    SDL_Quit();
}
void main_loop(SDL_Renderer *renderer){

}

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *screen = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0, 0, 640, 480};
    //SDL_Rect positionJoueur;
    SDL_Surface *joueur;
    SDL_Surface *mapSprite;
    //positionJoueur.x=150;
    //positionJoueur.y=150;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Erreur Init SDL");

    window = SDL_CreateWindow("Jeu C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if (window == NULL)
        SDL_ExitWithError("Init window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
        SDL_ExitWithError("init render");

// initialisation des sprites

    std::string filename = "background.bmp";
    std::string test = "bloc1.bmp";
    std::string sprite = "droite.bmp";

    screen = SDL_LoadBMP((std::string(RESOURCES_DIR) + filename).c_str());
    joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + sprite).c_str());

    if (screen == NULL)
        SDL_ExitWithError("Init picture ");


//Creation carte

    Carte carte(renderer);
    carte.lectureFichier();
    carte.changerCarte(screen);

//Affichage du joueur + background

    Player player(renderer);
    player.draw(screen);
    //SDL_BlitSurface(joueur, NULL, screen, &positionJoueur);
    texture = SDL_CreateTextureFromSurface(renderer, screen);


    if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0)
        SDL_ExitWithError("SDL_QueryTexture ");

    if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
        SDL_ExitWithError("SDL_RenderCopy");

    SDL_RenderPresent(renderer);

    double maxX = 10;
    double maxY = 10;
    double ax = 0.25;
    double vx = 0;
    double vy = 0;


    int continuer = 1;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYUP:
                player.remiseAZeroAcceleration();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        player.deplacerDroite(carte);
                        break;

                    case SDLK_LEFT:
                        player.deplacerGauche(carte);
                        break;

                    case SDLK_UP:
                        player.deplacerHaut(carte);
                        break;

                    case SDLK_DOWN:
                        player.deplacerBas(carte);
                        break;
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
                screen = SDL_LoadBMP((std::string(RESOURCES_DIR) + filename).c_str());
                carte.changerCarte(screen);
                player.draw(screen);
                texture = SDL_CreateTextureFromSurface(renderer, screen);
                SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h);
                SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
                SDL_RenderPresent(renderer);
                break;
        }
    }



    SDL_FreeSurface(joueur);
    SDL_FreeSurface(screen);
    clean_resources(window, renderer, texture);
    return EXIT_SUCCESS;
}


void SDL_ExitWithError(const char *string) {
    SDL_Log("Erreur : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
