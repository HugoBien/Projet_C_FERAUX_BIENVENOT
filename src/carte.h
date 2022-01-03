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
    }
    int peutSeDeplacer(int x, int y){
        int res = 1;
        x=x/hauteur;
        y=y/largeur;
        printf("%i , %i\n",x,y );
        printf("%c : map \n",map[x][y] );
        if(map[x][y]=='1'){
            res=0;
        }
        return res;
    }

    SDL_Rect position;
    int hauteur;
    int largeur;
    char ** map;
};

// liste chainer
// maloc
// ecriture fichier
// erreur lecture de fichier