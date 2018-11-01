#pragma once
#include "Enemy.h"

class Fire: public Enemy{
    public:
        Fire(int posX, int posY);
        void incPos(){m_pos.x--;}
        void incPos(int x){m_pos.x+=x;}
        SDL_Surface* getFrame(void);
        SDL_Surface* getFrameNoInc(void);

		//---------------------------------------------------------------fonctions apportées par PhysicObjet
		void move(){};
		void accelerate(){};
		void collisionReaction(Uint32 typeFlag){};

		Uint32 getTypeFlag(){return m_globbox.typeFlag;}
		int getVulnerability(){return m_globbox.vulnerabilityFrame;}
		s_hitbox getGlobbox(){return (s_hitbox){.x=m_pos.x, .y=m_pos.y, .w=m_globbox.w,\
			.h=m_globbox.h, .typeFlag=m_globbox.typeFlag, .vulnerabilityFrame=m_globbox.vulnerabilityFrame};}
        s_hitbox *getHitbox(){return NULL;}
		void decVulnerability(){m_globbox.vulnerabilityFrame-=(m_globbox.vulnerabilityFrame==0)?0:1;}

        int getPos(){return m_pos.x;}
        int getPosY(){return m_pos.y;}
        s_vector getVelocity(){return m_velocity;}

        void setPos(s_vector pos, int valueMask){};
        void setVelocity(s_vector velocity, int valueMask){};
        void setAcceleration(s_vector acceleration, int valueMask){};

    private:
		s_vector m_pos;
		s_vector m_velocity;
		s_vector m_acceleration;
		s_hitbox m_globbox;
        Animation m_anim;
};
