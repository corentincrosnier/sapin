#include "Basic_santa.h"

Basic_santa::Basic_santa(int posX, int posY):m_animRun(Animation("./img/anim_enemy/enemy.png", 64, 64, 8)){
	m_pos=(s_vector){.x=posX, .y=posY};
	m_velocity={.x=-2, .y=0};
	m_acceleration={.x=0, .y=0};
	m_globbox={.x=m_pos.x, .y=m_pos.y, .w=40, .h=80, .typeFlag=BASIC_SANTA_F, .vulnerabilityFrame=0};
}

SDL_Surface* Basic_santa::getFrame(void){
    SDL_Surface *ret=m_animRun.getCurFrame();
    m_animRun.incCurFrame();
    return ret;
}

SDL_Surface* Basic_santa::getFrameNoInc(void){
    return m_animRun.getCurFrame();
}
