#pragma once
#include "PhysicObjet.h"
#include "Map.h"

#define GRAVITY_ACC 2 //---------en pixel/frame²

class Physic{
    public:
        Physic(Map *map);
		void physicFrame(SDL_Surface *screen);
		void addObjet(PhysicObjet *newObjet);
        void removeObjet(PhysicObjet *delObjet);
		void dispHitbox(SDL_Surface *screen);
    private:
		void collision(int hbIndex, Uint32 flag);
		void mapCollision(int hbIndex);
		bool isColliding();

        PhysicObjet **m_objet;
		Map *m_map;
        int m_objetNb=0, m_objetLen=0;
};
