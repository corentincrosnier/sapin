#pragma once
#include "Enemy.h"

enum e_bucheState{BASIC,BURN};

class Buche: public Enemy{
    public:
        Buche(int posX, int posY);
        void incPos(){m_pos.x--;}
        void incPos(int x){m_pos.x+=x;}
        SDL_Surface* getFrame(void);
        SDL_Surface* getFrameNoInc(void);

		//---------------------------------------------------------------fonctions apportées par PhysicObjet
		void move(){m_pos.x+=m_velocity.x, m_pos.x+=m_velocity.y;}
		void accelerate(){m_velocity.x+=m_acceleration.x, m_velocity.y+=m_acceleration.y;}
		void collisionReaction(Uint32 typeFlag);

		Uint32 getTypeFlag(){return m_globbox.typeFlag;}
		int getVulnerability(){return m_globbox.vulnerabilityFrame;}
		s_hitbox getGlobbox(){return (s_hitbox){.x=m_pos.x, .y=m_pos.y, .w=m_globbox.w,\
			.h=m_globbox.h, .typeFlag=m_globbox.typeFlag, .vulnerabilityFrame=m_globbox.vulnerabilityFrame};}
        s_hitbox *getHitbox(){return NULL;}
		void decVulnerability(){m_globbox.vulnerabilityFrame-=(m_globbox.vulnerabilityFrame==0)?0:1;}

        int getPos(){return m_pos.x;}
        int getPosY(){return m_pos.y;}
        s_vector getVelocity(){return m_velocity;}

        void setPos(s_vector pos, int valueMask){m_pos.x=(valueMask%3!=2)?pos.x:m_pos.x, m_pos.y=(valueMask%3!=1)?pos.y:m_pos.y;}
        void setVelocity(s_vector velocity, int valueMask){m_velocity.x=(valueMask%3!=2)?velocity.x:m_velocity.x,\
			m_velocity.y=(valueMask%3!=1)?velocity.y:m_velocity.y;}
        void setAcceleration(s_vector acceleration, int valueMask){m_acceleration.x=(valueMask%3!=2)?acceleration.x:m_acceleration.x,\
			m_acceleration.y=(valueMask%3!=1)?acceleration.y:m_acceleration.y;}

    private:
		s_vector m_pos;
		s_vector m_velocity;
		s_vector m_acceleration;
		s_hitbox m_globbox;
        Animation m_anim;
        Animation m_animFire;
		e_bucheState m_state=BASIC;
};
