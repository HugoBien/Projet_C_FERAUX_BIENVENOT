//
// Created by Hugo on 22/11/2021.
//

#ifndef SDL2_DEMO_PLAYER_H
#define SDL2_DEMO_PLAYER_H
#endif //SDL2_DEMO_PLAYER_H

#include <SDL.h>
//#include <string>

struct Player {
    Player(SDL_Renderer *renderer) : renderer(renderer) {
        positionJoueur.x = 150;
        positionJoueur.y = 150;
        joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + droite).c_str());
    }

    SDL_Renderer *renderer;
    SDL_Surface *joueur;
    SDL_Rect positionJoueur;
    std::string droite = "droite.bmp";
    std::string gauche = "gauche.bmp";
    std::string haut = "haut.bmp";
    std::string bas = "bas.bmp";

    double maxX = 10;
    double maxY = 10;
    double ax = 0.25;
    double vx = 0;
    double vy = 0;

    void draw(SDL_Surface *screen){
        SDL_BlitSurface(joueur, NULL, screen, &positionJoueur);
    }

    Carte deplacerDroite(Carte carte) {
        if (carte.peutSeDeplacer(positionJoueur.x + 1 + 42+ vx, positionJoueur.y) == 1) {
            if (vx < maxX) {
                vx += ax;
            }
            positionJoueur.x += 1 + vx;
            SDL_RenderClear(renderer);
            joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + droite).c_str());
        }
        return carte;
    }

    Carte deplacerGauche(Carte carte) {
        if (carte.peutSeDeplacer(positionJoueur.x - 1 - vx, positionJoueur.y) == 1) {
            if (vx > -maxX) {
                vx -= ax;
            }
            positionJoueur.x -= 1 - vx;
            SDL_RenderClear(renderer);
            joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + gauche).c_str());
        }
        return carte;
    }

    Carte deplacerHaut(Carte carte) {
        if (carte.peutSeDeplacer(positionJoueur.x, positionJoueur.y - 1 - vy) == 1) {
            if (vx > -maxY) {
                vy -= ax;
            }
            positionJoueur.y -= 1 - vy;
            SDL_RenderClear(renderer);
            joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + haut).c_str());
        }
        return carte;
    }

    Carte deplacerBas(Carte carte) {
        if (carte.peutSeDeplacer(positionJoueur.x, positionJoueur.y + 1 + 57 + vy) == 1) {
            if (vy < maxY) {
                vy += ax;
            }
            positionJoueur.y += 1 + vy;
            SDL_RenderClear(renderer);
            joueur = SDL_LoadBMP((std::string(RESOURCES_DIR) + bas).c_str());
        }
        return carte;
    }

    void remiseAZeroAcceleration(){
        vx = 0;
        vy = 0;
    }

    void lirePosition(){
        std::ifstream file("save.txt");
        if (file.is_open()) {
            std::string line;
            getline(file,line);
            positionJoueur.x= stoi(line);
            getline(file,line);
            positionJoueur.y = stoi(line);
            file.close();
        }
    }

    void ecrirePosition(){
        std::ofstream file("save.txt");
        if (file.is_open()) {
            file<<positionJoueur.x<<std::endl;
            file<<positionJoueur.y<<std::endl;
            file.close();
        }
    }


};