#pragma once
#include <iostream>
#include "Displayable.h"
#include <SDL/SDL_image.h>

#define SAPIN_F 1
#define BASIC_SANTA_F 2
#define FIRE_F 4
#define BUCHE_F 8
#define FIRE_BUCHE_F 16
#define COIN_F 32
#define SAPIN_BULLET_F 64
#define ALL_F 64+32+16+8+4+2+1

struct s_hitbox{
    int x,y;
    int w,h;
	Uint32 typeFlag;
	int vulnerabilityFrame;
};

struct s_vector{
    double x,y;
};

class PhysicObjet{
    public:
        PhysicObjet(){};
		virtual void move(void)=0;
		virtual void accelerate(void)=0;
		virtual void collisionReaction(Uint32 typeFlag)=0;

		virtual Uint32 getTypeFlag(void)=0;
		virtual int getVulnerability(void)=0;
        virtual s_hitbox getGlobbox(void)=0;
        virtual s_hitbox* getHitbox(void)=0;
		virtual void decVulnerability(void)=0;

        virtual int getPos(void)=0;
        virtual int getPosY(void)=0;
        virtual s_vector getVelocity(void)=0;

        virtual void setPos(s_vector pos, int valueMask)=0;
        virtual void setVelocity(s_vector velocity, int valueMask)=0;
		virtual void setAcceleration(s_vector acceleration, int valueMask)=0;
};
