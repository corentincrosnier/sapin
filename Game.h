#pragma once
#include "Physic.h"
#include "Map.h"
#include "Sapin.h"
#include "Basic_santa.h"
#include "Fire.h"
#include "Buche.h"
#include "Coin.h"

class Game{
    public:
        Game(SDL_Surface *screen);
        ~Game(){};
        void play(void);

    private:
        void getMapObstacle(void);
        void event(void);
        void display(void);
        void displayHUD(void);
        void displaySapin(void);
        void displayEnemy(void);
        void enemyDelete(int e);

        SDL_Surface *m_screen;
        SDL_Event m_event;
        Map m_map;
        Sapin m_sapin;
        Enemy **m_enemy;
        Physic m_physic;
        bool m_quit=false;
        int m_nbEnemy=0;
};
