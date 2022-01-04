#ifndef SDL2_DEMO_CARTE_H
#define SDL2_DEMO_CARTE_H

#endif //SDL2_DEMO_CARTE_H
#include <SDL.h>
#include <fstream>
#include "pile.h"

struct Carte{
    Carte(SDL_Renderer *renderer) : renderer(renderer){

        pileDePiece = new_Pile();
        pileDePiece = empile(pileDePiece, 15,15);
        pileDePiece = empile(pileDePiece, 10,2);
        pileDePiece = empile(pileDePiece, 8,8);
        pileDePiece = empile(pileDePiece, 7,5);



    }
    SDL_Renderer *renderer; // draw here
    SDL_Surface *bloc1 = SDL_LoadBMP((std::string(RESOURCES_DIR) + "bloc1.bmp").c_str());
    SDL_Surface *bloc2 = SDL_LoadBMP((std::string(RESOURCES_DIR) + "bloc2.bmp").c_str());
    SDL_Surface *piece = SDL_LoadBMP((std::string(RESOURCES_DIR) + "piece.bmp").c_str());


    void lectureFichier(){
        std::ifstream fileIni("carte.txt");
        int nbL=0;
        int nbC =0;
        if (fileIni.is_open()) {
            std::string line;
            nbL=0;
            nbC =0;
            while (getline(fileIni, line)) {
                nbL++;
                if(line.length()>nbC){
                    nbC = line.length();
                }
            }
        }
        fileIni.close();

        map = new char*[nbL];
        hauteur = nbL;
        largeur = nbC;
        for (int i = 0; i < nbL ; ++i) {
            map[i]= new char[nbL];
        }


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

        if (!est_vide_Pile(pileDePiece)){
            position.x=pileDePiece->posX*32;
            position.y=pileDePiece->posY*32;

            SDL_BlitSurface(piece,NULL,surface,&position);
        }
    }
    int peutSeDeplacer(int x, int y){
        int res = 1;
        //printf("X : %i, Y: %i\n",x,y);
        float px=static_cast< float >(x);
        px = px/640*largeur;
        float py=static_cast< float >(y);
        py = py/640*hauteur;
        //printf("%i , %i _ hauteur : %i, largeur : %i\n",static_cast<int>(px),static_cast<int>(py),hauteur,largeur );
        //printf("%c : map \n",map[x][y] );
        x = static_cast<int>(px);
        y = static_cast<int>(py);
        if(map[x][y]=='1'){
            res=0;
        }
        if(!est_vide_Pile(pileDePiece)) {
            if ((pileDePiece->posX == x || pileDePiece->posX == x+1) && (pileDePiece->posY == y || pileDePiece->posY == y+1)) {
                pileDePiece = depile(pileDePiece);
            }
        }

        return res;
    }

    SDL_Rect position;
    int hauteur;
    int largeur;
    char ** map;
    Pile *pileDePiece;
};

// liste chainer
// maloc
// ecriture fichier
// erreur lecture de fichier