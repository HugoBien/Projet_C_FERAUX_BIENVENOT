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


void redraw(SDL_Surface *screen, Carte carte, Player player,std::string background,SDL_Renderer *renderer,SDL_Rect dest_rect,
            SDL_Texture *texture){

    screen = SDL_LoadBMP((std::string(RESOURCES_DIR) + background).c_str());
    carte.changerCarte(screen);
    player.draw(screen);
    texture = SDL_CreateTextureFromSurface(renderer, screen);
    SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);

}


int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *screen = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0, 0, 640, 480};
    SDL_Rect positionSouris;
    SDL_Surface *joueur;
    SDL_Event event;

    // initialisation des sprites

    std::string menu ="menu.bmp";
    std::string background = "background.bmp";

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Erreur Init SDL");

    window = SDL_CreateWindow("Jeu C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if (window == NULL)
        SDL_ExitWithError("Init window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
        SDL_ExitWithError("init render");


    screen = SDL_LoadBMP((std::string(RESOURCES_DIR) + menu).c_str());

    if (screen == NULL)
        SDL_ExitWithError("Init picture ");

    texture = SDL_CreateTextureFromSurface(renderer, screen);

    if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0)
        SDL_ExitWithError("SDL_QueryTexture ");

    if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
        SDL_ExitWithError("SDL_RenderCopy");

// creation du joueur et de la carte

    Player player(renderer);
    Carte carte(renderer);
    carte.lectureFichier();

// affichage du menu

    SDL_RenderPresent(renderer);

// gestion du menu

    int continuerMenu=1;
    while(continuerMenu==1){
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                SDL_FreeSurface(joueur);
                SDL_FreeSurface(screen);
                clean_resources(window, renderer, texture);
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&positionSouris.x,&positionSouris.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        // commencer une nouvelle partie
                        if(positionSouris.x>=177 && positionSouris.x<=452 && positionSouris.y <= 299 && positionSouris.y >= 245){
                            continuerMenu=0;
                        }
                            // continuer la partie
                        else if(positionSouris.x>=177 && positionSouris.x<=452 && positionSouris.y <= 385 && positionSouris.y >= 331){
                            player.lirePosition();
                            continuerMenu=0;
                        }
                            // quitter le jeu
                        else if(positionSouris.x>=177 && positionSouris.x<=452 && positionSouris.y <= 468 && positionSouris.y >= 414){
                            SDL_FreeSurface(joueur);
                            SDL_FreeSurface(screen);
                            clean_resources(window, renderer, texture);
                        }
                        break;
                }

            case SDL_MOUSEBUTTONUP:
                break;
        }
    }

    redraw(screen,carte,player,background,renderer,dest_rect,texture);

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
                        carte = player.deplacerDroite(carte);
                        break;

                    case SDLK_LEFT:
                        carte = player.deplacerGauche(carte);
                        break;

                    case SDLK_UP:
                        carte = player.deplacerHaut(carte);
                        break;

                    case SDLK_DOWN:
                        carte = player.deplacerBas(carte);
                        break;

                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
                redraw(screen,carte,player,background,renderer,dest_rect,texture);
                break;
        }
    }

    player.ecrirePosition();
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