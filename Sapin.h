#pragma once
#include "Animation.h"
#include "PhysicObjet.h"


enum e_state{RUN, JUMP, CROUCH};

class Sapin: public PhysicObjet{
    public:
        Sapin(int posX, int posY);
        ~Sapin(){};
        void display(SDL_Surface *screen);
		void display();
        bool isDead(){return m_dead;}
        void incPos(){m_pos.x++;}
        void incPos(int x){m_pos.x+=x;}
        void resetPos(){m_pos.x=0;}
        void jump();
		void shoot();
        SDL_Surface* getFrame();
        SDL_Surface* getFrameNoInc();

		//---------------------------------------------------------------fonctions apportées par PhysicObjet
		void move(){m_pos.x+=m_velocity.x, m_pos.y+=m_velocity.y;}
		void accelerate(){m_velocity.x+=m_acceleration.x, m_velocity.y+=m_acceleration.y;}
		void collisionReaction(Uint32 typeFlag){
			//if(m_round<8){
			if(typeFlag==COIN_F){
				m_score+=7;
				std::cout << std::endl << "Score=" << m_score;
			}
			else{
				//m_velocity.x=0;
				//m_acceleration.x=0.7;
				jump(2);
				m_globbox.vulnerabilityFrame=50;
				if(typeFlag==FIRE_BUCHE_F)
					std::cout << "FFIRE bUCHE cOllison" << std::endl;
			}

			//	m_round++;
			//}
			//else{

			//	m_acceleration.x=0;
			//}
		}
		

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
        void jump(int a);

		int m_round=0;
        int m_lifeMax=3, m_life=m_lifeMax;
		int m_score=0;
		s_vector m_pos;
		s_vector m_velocity;
		s_vector m_acceleration;
		s_hitbox m_globbox;
        bool m_dead=false;
        Animation m_animRun, m_animJump;
//		Bullet *m_bullets;
        e_state m_state=RUN, m_stateNext=RUN;
};
