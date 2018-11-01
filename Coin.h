#pragma once
#include "Enemy.h"

class Coin: public Enemy{
    public:
		Coin(int posX, int posY);
        void incPos(){m_pos.x--;}
        void incPos(int x){m_pos.x+=x;}
        SDL_Surface* getFrame(void);
        SDL_Surface* getFrameNoInc(void);

		void move(){};
		void accelerate(){};
		void collisionReaction(Uint32 typeFlag){
			m_collected=true;
			m_globbox.vulnerabilityFrame=1;
		}

		Uint32 getTypeFlag(){return m_globbox.typeFlag;}
		int getVulnerability(){return m_globbox.vulnerabilityFrame;}
		s_hitbox getGlobbox(){return (s_hitbox){.x=m_pos.x, .y=m_pos.y, .w=m_globbox.w,\
			.h=m_globbox.h, .typeFlag=m_globbox.typeFlag, .vulnerabilityFrame=m_globbox.vulnerabilityFrame};}
        s_hitbox *getHitbox(){return NULL;}
		void decVulnerability(){};

        int getPos(){return m_pos.x;}
        int getPosY(){return m_pos.y;}
        s_vector getVelocity(){return {.x=0, .y=0};}

        void setPos(s_vector pos, int valueMask){m_pos.x=(valueMask%3!=2)?pos.x:m_pos.x, m_pos.y=(valueMask%3!=1)?pos.y:m_pos.y;}
        void setVelocity(s_vector velocity, int valueMask){};
        void setAcceleration(s_vector acceleration, int valueMask){};

	private:
		s_vector m_pos;
		s_hitbox m_globbox;
		Animation m_anim;
		bool m_collected;
};
