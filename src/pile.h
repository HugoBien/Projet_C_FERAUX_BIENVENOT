//
// Created by Julien on 02/01/2022.
//

#ifndef SDL2_DEMO_PILE_H
#define SDL2_DEMO_PILE_H

#include <iostream>

typedef struct Pile{
    int posX;
    int posY;
    Pile *suivant;
}Pile;

Pile* new_Pile(){
    Pile *p = nullptr;
    return p;
}
int est_vide_Pile(Pile *p){

    return p==0;
}
Pile* empile(Pile *p, int px, int py){
    Pile *pile;
    pile = new Pile;
    pile->posX = px;
    pile->posY = py;
    pile->suivant = p;
    return pile;
}
Pile* depile(Pile *p){
    if(!est_vide_Pile(p)){
        return p->suivant;
    }
    return nullptr;
}





#endif //SDL2_DEMO_PILE_H
