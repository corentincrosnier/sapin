#include "Buche.h"

Buche::Buche(int posX, int posY):m_anim(Animation("./img/anim_enemy/Buche.png", 32, 32, 4)), \
m_animFire(Animation("./img/anim_enemy/BucheFire.png",32,40,4)){
	m_pos=(s_vector){.x=posX, .y=posY};
	m_velocity={.x=-5, .y=0};
	m_acceleration={.x=0, .y=0};
	m_globbox={.x=m_pos.x, .y=m_pos.y, .w=30, .h=80, .typeFlag=BUCHE_F, .vulnerabilityFrame=0};
}

void Buche::collisionReaction(Uint32 typeFlag){
	if(typeFlag==FIRE_F){
		m_globbox.typeFlag=FIRE_BUCHE_F;
		m_state=BURN;
	}
	std::cout << "Buche is Burning" << std::endl;
}

SDL_Surface* Buche::getFrame(void){
    SDL_Surface *ret=(m_state==BURN)?m_animFire.getCurFrame():m_anim.getCurFrame();
	if(m_state==BURN)
    	m_animFire.incCurFrame();
	else
		m_anim.incCurFrame();
    return ret;
}

SDL_Surface* Buche::getFrameNoInc(void){
    return (m_state==BURN)?m_animFire.getCurFrame():m_anim.getCurFrame();
}
