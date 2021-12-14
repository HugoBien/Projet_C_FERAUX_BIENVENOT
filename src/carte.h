#ifndef SDL2_DEMO_CARTE_H
#define SDL2_DEMO_CARTE_H

#endif //SDL2_DEMO_CARTE_H
#include <SDL.h>
#include <fstream>

struct Carte{
    Carte(SDL_Renderer *renderer) : renderer(renderer){

    }
    SDL_Renderer *renderer; // draw here
    SDL_Surface *bloc1 = SDL_LoadBMP((std::string(RESOURCES_DIR) + "bloc1.bmp").c_str());
    SDL_Surface *bloc2 = SDL_LoadBMP((std::string(RESOURCES_DIR) + "bloc2.bmp").c_str());


    void lectureFichier(){
        std::ifstream file("carte.txt");
        if (file.is_open()) {
            std::string line;
            int numeroLine=0;
            while (getline(file, line)) {
                // using printf() in all tests for consistency
                for(int i= 0; i < line.length();i++ ){
                    //printf("%c\n",line[i]);
                    map[numeroLine][i]=line[i];
                }
                numeroLine++;
            }
            file.close();
        }
    }

    void afficher(){
        for(int i = 0; i<largeur; i++){
            for(int j = 0; j<hauteur; j++){
                printf("%c",map[i][j]);
            }
            printf("\n");
        }
    }
    void changerCarte(SDL_Surface *surface){
        for(int i = 0; i<largeur;i++){
            for(int j = 0; j<hauteur;j++){
                position.x=i*32;
                position.y=j*32;
                switch (map[j][i]) {
                    case '0':
                        break;
                    case '1':
                        SDL_BlitSurface(bloc1,NULL,surface,&position);
                        break;
                    case '2':
                        SDL_BlitSurface(bloc2,NULL,surface,&position);
                        break;
                }
            }
        }
    }
    SDL_Rect position;
    int hauteur = 20;
    int largeur = 20;
    char map[20][20];
    //dynamique
};