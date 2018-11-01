#include "Fire.h"

Fire::Fire(int posX, int posY):m_anim(Animation("./img/anim_fire/onFire.png", 32, 32, 6)){
	m_pos=(s_vector){.x=posX, .y=posY};
	m_velocity={.x=0, .y=0};
	m_acceleration={.x=0, .y=0};
	m_globbox={.x=m_pos.x, .y=m_pos.y, .w=32, .h=32, .typeFlag=FIRE_F, .vulnerabilityFrame=0};
}

SDL_Surface* Fire::getFrame(void){
    SDL_Surface *ret=m_anim.getCurFrame();
    m_anim.incCurFrame();
    return ret;
}

SDL_Surface* Fire::getFrameNoInc(void){
    return m_anim.getCurFrame();
}
