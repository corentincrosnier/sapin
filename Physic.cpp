#include "Physic.h"
#define PHYSIC_OBJET_REALLOC_ADD 16

Physic::Physic(Map *map){
	m_map=map;
}

void Physic::physicFrame(SDL_Surface *screen){
	int i;
	s_hitbox tmp;
	SDL_Rect rect;
	for(i=0;i<m_objetNb;i++){
		m_objet[i]->accelerate();
		m_objet[i]->move();
		//tmp=m_objet[i]->getGlobbox();
		//rect={.x=tmp.x, .y=tmp.y, .w=tmp.w, .h=tmp.h};
		//SDL_FillRect(screen,&rect,0xffff00);
	}
	for(i=0;i<m_objetNb;i++){
		switch(m_objet[i]->getTypeFlag()){
			case SAPIN_F:
				mapCollision(i);
				collision(i,ALL_F);
			break;
			case BASIC_SANTA_F:
				mapCollision(i);
				//collision(i,SAPIN_F);
			break;
			case FIRE_F:
				collision(i,BUCHE_F | SAPIN_F);
			break;
			case BUCHE_F:
				mapCollision(i);
				collision(i,FIRE_F | SAPIN_F);
			break;
		}
		if(m_objet[i]->getPosY()>m_map->getFloorH()+1)
			m_objet[i]->setAcceleration((s_vector){.x=0, .y=-2},2);
		if(m_objet[i]->getVulnerability()>0)
			std::cout << m_objet[i]->getVulnerability() << std::endl;
		m_objet[i]->decVulnerability();
//		std::cout << m_objet[i]->getTypeFlag() << "    " << m_objet[i]->m_screen->w << std::endl;
	}
}

void Physic::collision(int hbIndex, Uint32 flag){
	int i;
	s_hitbox curHb=m_objet[hbIndex]->getGlobbox();
	s_hitbox tmpHb;
	for(i=hbIndex+1;i<m_objetNb;i++){
		if(curHb.vulnerabilityFrame==0 || (m_objet[i]->getTypeFlag()==COIN_F)){
			if(((flag & m_objet[i]->getTypeFlag())!=0) && (m_objet[i]->getVulnerability()==0)){
				tmpHb=m_objet[i]->getGlobbox();
				if( ((curHb.x<tmpHb.x)?(tmpHb.x-curHb.x)<curHb.w:(curHb.x-tmpHb.x)<tmpHb.w) &&\
						((curHb.y<tmpHb.y)?(tmpHb.y-curHb.y)<curHb.h:(curHb.y-tmpHb.y)<tmpHb.h) ){
					m_objet[i]->collisionReaction(curHb.typeFlag);
					m_objet[hbIndex]->collisionReaction(tmpHb.typeFlag);
				}
			}
		}
	}
}

void Physic::mapCollision(int hbIndex){
	s_hitbox tmpHitbox;
	tmpHitbox=m_objet[hbIndex]->getGlobbox();
	if(m_objet[hbIndex]->getPosY()<=m_map->getFloorH()){
		m_objet[hbIndex]->setAcceleration((s_vector){.x=0, .y=0},3);
		m_objet[hbIndex]->setVelocity((s_vector){.x=0, .y=0},2);
		m_objet[hbIndex]->setPos((s_vector){.x=0, .y=m_map->getFloorH()+1},2);
	}
}

void Physic::addObjet(PhysicObjet *newObjet){
    if(m_objetNb+1>=m_objetLen){
        if(m_objetNb>0){
            std::cout << "Sa vas planter" << std::endl;
        }
        m_objet=new PhysicObjet*[m_objetLen+PHYSIC_OBJET_REALLOC_ADD];
        //if(!m_objet)
        m_objetLen+=PHYSIC_OBJET_REALLOC_ADD;
    }
    m_objet[m_objetNb]=newObjet;
    m_objetNb++;
}

void Physic::removeObjet(PhysicObjet *delObjet){
    int i, d;
    for(i=0; i<m_objetNb; i++){
        if(m_objet[i]==delObjet){
            for(d=i; d<m_objetNb-1; d++){
                m_objet[d]=m_objet[d+1];
            }
            std::cout << "susscefull delete" << std::endl;
            m_objetNb--;
            break;
        }
    }
}
