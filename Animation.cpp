#include "Animation.h"

Animation::Animation(SDL_Surface *img, int w, int h, int nbFrames):m_nbFrames(nbFrames){
    loadAnim(img, w, h);
}

Animation::Animation(char *imgWay, int w, int h, int nbFrames):m_nbFrames(nbFrames){
	SDL_Surface *img=IMG_Load(imgWay);
    if(img){
        loadAnim(img, w, h);
        SDL_FreeSurface(img);
    }
}

Animation::~Animation(){
    int i;
    for(i=0; i<m_nbFrames; i++){
        SDL_FreeSurface(m_frame[i]);
    }
    free(m_frame); //----je crois que delete[] avec malloc n'est pas safe
}

void Animation::loadAnim(SDL_Surface *img, int w, int h){
    int i, x=0, y=0;
    SDL_Rect rect;
    m_frame=(SDL_Surface**)malloc(sizeof(*m_frame)*m_nbFrames);
    for(i=0; i<m_nbFrames; i++){
        if(x>=img->w){
            x=0;
            y+=h;
        }
        m_frame[i]=SDL_CreateRGBSurface(img->flags, w, h, 32, 0, 0, 0, 0);
        rect=(SDL_Rect){.x=x, .y=y, .w=w, .h=h};
        SDL_BlitSurface(img, &rect, m_frame[i], NULL);
        x+=w;
    }
    m_isLoad=true;
}

int Animation::incCurFrame(void){
    m_curFrame=(m_curFrame+1)%m_nbFrames;
    return m_curFrame;
}
