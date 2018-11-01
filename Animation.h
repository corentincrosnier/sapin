#pragma once
#include <iostream>
#include "Displayable.h"
#include <SDL/SDL_image.h>

//ALPHA A GERER
class Animation{
    public:
        Animation(){};
        Animation(SDL_Surface *img, int w, int h, int nbFrames);//on s'en fou
        Animation(char *imgWay, int w, int h, int nbFrames);
         ~Animation();
        SDL_Surface* getCurFrame(void){return m_frame[m_curFrame];}
        int incCurFrame(void);
        bool isLoad(void){return m_isLoad;}

    private:
        void loadAnim(SDL_Surface *img, int w, int h);

        SDL_Surface **m_frame;
        int m_nbFrames, m_curFrame=0;
        bool m_isLoad=false;
};
