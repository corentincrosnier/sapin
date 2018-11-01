#include "Sapin.h"

Sapin::Sapin(int posX, int posY):m_animRun(Animation("./img/anim_sapin/Course/sapin 2.png", 64, 64, 6)),\
m_animJump(Animation("./img/anim_sapin/Saut/sapin 6.png", 64, 64, 6)){
    if(m_animRun.isLoad() && m_animJump.isLoad())
        std::cout << "sapin is load" << std::endl;
	m_velocity={.x=10, .y=0};
	m_acceleration={.x=0, .y=0};
	m_pos.x=posX;
	m_pos.y=posY;
	m_globbox={.x=m_pos.x, .y=m_pos.y, .w=30, .h=80, .typeFlag=SAPIN_F, .vulnerabilityFrame=0};
}

bool first;

void Sapin::display(){
    SDL_Surface *frame=getFrame();
    //SDL_Rect rect={.x=30, .y=m_screen->h-m_map.getFloorH()-frame->h};
    SDL_Rect rect={.x=30, .y=m_screen->h-frame->h-m_pos.y};
    SDL_BlitSurface(frame, NULL, m_screen, &rect);
}

/*
void Sapin::collisionReaction(Uint32 typeFlag){
	bool First
	m_velocity.x=0;
	m_acceleration.x+=2;
	jump();
}*/

void Sapin::jump(){
	m_stateNext=(m_state!=JUMP)?JUMP:m_stateNext;
	m_velocity.y=(m_stateNext==JUMP)?20:0;
}

void Sapin::shoot(){
	
}

void Sapin::jump(int a){
	m_stateNext=(m_state!=JUMP)?JUMP:m_stateNext;
	m_velocity.y=(m_stateNext==JUMP)?20:0;
}

SDL_Surface* Sapin::getFrame(void){
    SDL_Surface *ret=getFrameNoInc();
    m_state=m_stateNext;
    switch(m_state){
        case RUN:
            m_animRun.incCurFrame();
            break;
        case JUMP:
            if(!m_animJump.incCurFrame())
                m_stateNext=RUN;
            break;
    }
    return ret;
}

SDL_Surface* Sapin::getFrameNoInc(void){
    switch(m_state){
        case RUN:
            return m_animRun.getCurFrame();
        case JUMP:
            return m_animJump.getCurFrame();
    }
    return NULL;
}
