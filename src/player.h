//
// Created by Hugo on 22/11/2021.
//

#ifndef SDL2_DEMO_PLAYER_H
#define SDL2_DEMO_PLAYER_H
#endif //SDL2_DEMO_PLAYER_H

player(SDL_Renderer *renderer){

}

void draw()
{
    SDL_Rect src = sprites[state].rect(timestamp);
    SDL_Rect dest = { int(x)-sprite_w/2, int(y)-sprite_h, sprite_w, sprite_h };
    SDL_RenderCopyEx(renderer, sprites[state].texture, &src, &dest, 0, nullptr, backwards ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

int x = 0;
int y = 0;
std::string sprites="";
