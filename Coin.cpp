#include "Coin.h"

Coin::Coin(int posX, int posY):m_anim(Animation("./img/map/tree.png",32,32,1)){
	m_pos.x=posX;
	m_pos.y=posY;
	m_globbox={.x=posX, .y=posY, .w=32, .h=32, .typeFlag=COIN_F, .vulnerabilityFrame=0};
	m_collected=false;
}

SDL_Surface* Coin::getFrame(void){
	SDL_Surface *ret=(m_collected)?SDL_CreateRGBSurface(0,0,0,0,0,0,0,0):m_anim.getCurFrame();
	m_anim.incCurFrame();
	return ret;
}

SDL_Surface* Coin::getFrameNoInc(void){
	return (m_collected)?SDL_CreateRGBSurface(0,0,0,0,0,0,0,0):m_anim.getCurFrame();
}
