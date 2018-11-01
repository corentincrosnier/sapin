#pragma once
#include "Animation.h"
#include <unistd.h>
#include <time.h>
#define VOID_OBSTACLE (s_Obstacle){.x=0, .y=0, .w=0, .type=VOID}
#define MAX_PATTERN 20

enum e_Obstacle{VOID=0,FIRE,BUCHE,LUTIN,SANTA,REINDEER,COIN,BULLET};

struct s_floorH{
	int x,y,p;
};

struct s_Obstacle{
	int x,y,w;
	e_Obstacle type;
};

struct s_Pattern{
	int width;
	int nbObstacle;
	s_Obstacle *obstacle;
};

struct s_plan{
	int depth;
	SDL_Surface *texture;
};

class Map{
    public:
        Map();
        ~Map(){};
        void display(SDL_Surface *screen, int pos);
        int getLength(void){return m_length;}
        int getFloorH(void){return m_floorH;}
		//s_Obstacle getNextObstacle(void){return m_obstacle[m_nextObsIndex];} //  <---Pour savoir si on spawn un énemi & la physique des trous
        s_Obstacle getNextObstacle(SDL_Surface *screen, int pos);
		int getMapScrolling(){return m_mapScrolling;}
		void createMap(SDL_Surface *screen, int length, bool usePatterns);   //------preGen: Charge une map entiere avant la boucle	

    private:
		void scrollObstacle();
		void initPattern();
		void dispFloor(SDL_Surface *screen, int pos);

		int m_mapScrolling=8;
        int m_floorH=110;
        int m_length=0;
		int m_currentScreenIndex;
		bool m_preGen=true;
        int m_nbPatternTemplate;
		SDL_Surface *m_mapTexture=NULL;
		SDL_Surface *m_background;
		SDL_Surface *m_floor;
		SDL_Surface *m_backFloor;
		SDL_Surface *m_tree;
		SDL_Surface *m_ground;
		s_Pattern *m_patternTemplate;
		int m_patternType[MAX_PATTERN];
        int m_curPattern=0, m_curTemplateObs=0, m_curTemplateX=0;
        int m_nbPattern=0;
        //s_plan *m_texture[5];*/
};
