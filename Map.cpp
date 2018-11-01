#include "Map.h"
#define DEPART screen->w
#define ARRIVE 100

Map::Map(){
	m_background=IMG_Load("./img/map/night_sky.png");
	m_ground=IMG_Load("./img/map/ground.png");
	m_floor=IMG_Load("./img/map/floor.png");
	m_backFloor=IMG_Load("./img/map/backFloor.png");
	m_tree=IMG_Load("./img/map/tree.png");
	initPattern();
}

void Map::createMap(SDL_Surface *screen, int length, bool usePatterns){   //------preGen: Charge une map entiere avant la boucle	
	std::cout << "Creating map:" << std::endl;
	int i;															   //------!preGen: Charge la map en cours de jeu !!(pas implementer)!!
	int newObstacle=0;
    static bool firstTime=true;
	m_nbPattern=0;

	m_floorH=110;
	
	if(usePatterns){
		int r,p;
		int w=0;
		int o=0;
        m_curPattern=0;
        m_curTemplateObs=0;
        m_curTemplateX=(firstTime?DEPART:0)+m_length;
		while(m_nbPattern < MAX_PATTERN){
			r=rand()%m_nbPatternTemplate;
			if(length-w<m_patternTemplate[r].width){
				break;
			}
			m_patternType[m_nbPattern]=r;
			m_nbPattern++;
			w+=m_patternTemplate[r].width;
            newObstacle+=m_patternTemplate[r].nbObstacle;
		}
        std::cout << "reach end of map:" << m_nbPattern << "p ; " << newObstacle << "o" << std::endl;
		m_length+=w+100;
		std::cout << std::endl;
	}
	else{
	}
    firstTime=false;
}

s_Obstacle Map::getNextObstacle(SDL_Surface *screen, int pos){
    s_Obstacle obs;
    while(m_curTemplateObs>=m_patternTemplate[m_patternType[m_curPattern]].nbObstacle && m_curPattern<m_nbPattern){
        m_curTemplateObs=0;
        m_curPattern++;
		m_curTemplateX+=m_patternTemplate[m_patternType[m_curPattern]].width;
    }
    if(m_curPattern>=m_nbPattern) 
        return VOID_OBSTACLE;
    obs.x=m_patternTemplate[m_patternType[m_curPattern]].obstacle[m_curTemplateObs].x+m_curTemplateX;
    if(obs.x-pos<screen->w+100){
        obs.y=m_patternTemplate[m_patternType[m_curPattern]].obstacle[m_curTemplateObs].y;
        obs.type=m_patternTemplate[m_patternType[m_curPattern]].obstacle[m_curTemplateObs].type;
        m_curTemplateObs++;
        return obs;
    }
    return VOID_OBSTACLE;
    
}

void Map::display(SDL_Surface *screen, int pos){
	int i=0,j=1;
	SDL_Rect rect;
	SDL_BlitSurface(m_background,NULL,screen,NULL);
	dispFloor(screen,pos);
	if(m_length-(pos+screen->w)<=m_mapScrolling)
		createMap(screen,1000,true);
}

void Map::dispFloor(SDL_Surface *screen, int pos){
	int i=0,j;
	int offset=pos%m_ground->w;
	SDL_Rect rect;
	while(i*m_ground->w-offset<=screen->w){
		rect.x=-offset+m_ground->w*i;
		rect.y=screen->h-m_floorH-8;
		SDL_BlitSurface(m_floor,NULL,screen,&rect);
		j=0;
		while(m_floor->h+j*m_ground->h<m_floorH){
			rect.x=-offset+m_ground->w*i;
			rect.y=screen->h-(m_floorH-(m_floor->h)-j*m_ground->h)-8;
			SDL_BlitSurface(m_ground,NULL,screen,&rect);
			j++;
		}
		i++;
	}
}

void Map::initPattern(){
    m_nbPatternTemplate=3;
	m_patternTemplate=new s_Pattern[m_nbPatternTemplate];
	m_patternTemplate[0].nbObstacle=0;
	m_patternTemplate[0].obstacle=NULL;
	m_patternTemplate[0].width=320;
	
	m_patternTemplate[1].nbObstacle=3;
	m_patternTemplate[1].obstacle=new s_Obstacle[3];
	m_patternTemplate[1].width=6*64+32;
	m_patternTemplate[1].obstacle[0].type=SANTA;
	m_patternTemplate[1].obstacle[0].x=0;
	m_patternTemplate[1].obstacle[0].y=m_floorH;
	m_patternTemplate[1].obstacle[1].type=FIRE;
	m_patternTemplate[1].obstacle[1].x=128;
	m_patternTemplate[1].obstacle[1].y=m_floorH;
	m_patternTemplate[1].obstacle[2].type=COIN;
	m_patternTemplate[1].obstacle[2].x=288;
	m_patternTemplate[1].obstacle[2].y=m_floorH+100;

	m_patternTemplate[2].nbObstacle=3;
	m_patternTemplate[2].obstacle=new s_Obstacle[3];
	m_patternTemplate[2].width=8*64;
	m_patternTemplate[2].obstacle[0].type=COIN;
	m_patternTemplate[2].obstacle[0].x=0;
	m_patternTemplate[2].obstacle[0].y=m_floorH;
	m_patternTemplate[2].obstacle[1].type=FIRE;
	m_patternTemplate[2].obstacle[1].x=160;
	m_patternTemplate[2].obstacle[1].y=m_floorH;
	m_patternTemplate[2].obstacle[2].type=BUCHE;
	m_patternTemplate[2].obstacle[2].x=320;
	m_patternTemplate[2].obstacle[2].y=m_floorH;
	std::cout << "patternTemplate loaded" << std::endl;
}
