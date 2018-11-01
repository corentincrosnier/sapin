#pragma once
#include "Animation.h"
#include "PhysicObjet.h"

class Enemy: public PhysicObjet{
    public:
        Enemy():PhysicObjet(){};
        virtual void incPos()=0;
        virtual void incPos(int x)=0;
        virtual SDL_Surface* getFrame(void)=0;
        virtual SDL_Surface* getFrameNoInc(void)=0;
};
