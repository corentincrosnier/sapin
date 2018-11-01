#include "Game.h"
#include <unistd.h>

#define FRAME_RATE 25
#define FRAME_DURATION (1/FRAME_RATE)*1000
#define MAX_ENEMY 100 

Game::Game(SDL_Surface *screen):m_screen(screen), m_sapin(Sapin(0,m_map.getFloorH()+1)), m_physic(Physic(&m_map)){
    int i;
    m_physic.addObjet(&m_sapin);
	m_map.createMap(m_screen, 3*m_screen->w, true);
    m_enemy=new Enemy*[MAX_ENEMY];
    getMapObstacle();
}

void Game::getMapObstacle(void){
    s_Obstacle obs;
    while((obs=m_map.getNextObstacle(m_screen, m_sapin.getPos())).type && m_nbEnemy<MAX_ENEMY){
        switch(obs.type){
            case SANTA:
                m_enemy[m_nbEnemy]=new Basic_santa(obs.x, obs.y);
                m_physic.addObjet(m_enemy[m_nbEnemy]);
                m_nbEnemy++;
                break;
            case FIRE:
                m_enemy[m_nbEnemy]=new Fire(obs.x, obs.y);
                m_physic.addObjet(m_enemy[m_nbEnemy]);
                m_nbEnemy++;
                break;
            case BUCHE:
                m_enemy[m_nbEnemy]=new Buche(obs.x, obs.y);
                m_physic.addObjet(m_enemy[m_nbEnemy]);
                m_nbEnemy++;
                break;
			case COIN:
                m_enemy[m_nbEnemy]=new Coin(obs.x, obs.y);
                m_physic.addObjet(m_enemy[m_nbEnemy]);
                m_nbEnemy++;
				break;
        }
    }
}

void Game::play(void){
	int actualTime=0, lastFrameTime=0, sleepTime=0;
	int frameDuration=FRAME_DURATION;
	lastFrameTime=SDL_GetTicks();
    while(!m_quit){
        display(); 
        event();   //<---------------------------Mettre le usleep dedans ?? avec le temp de calcul de la frame
        getMapObstacle();
		m_physic.physicFrame(m_screen);
        if(m_sapin.getPos()>=m_map.getLength())
            m_sapin.resetPos();
		actualTime=SDL_GetTicks();
		if((sleepTime=frameDuration-(actualTime-lastFrameTime))>10){
			SDL_Delay(sleepTime);
		}
        SDL_Delay(20);
		//std::cout << "FFFF=" << sleepTime << std::endl;
		lastFrameTime=actualTime;
    }
}

void Game::display(void){
	SDL_FillRect(m_screen,NULL,SDL_MapRGB(m_screen->format,0,0,0));
    m_map.display(m_screen, m_sapin.getPos());
    //displaySapin();
	m_sapin.display();
    displayEnemy();
    displayHUD();
    SDL_Flip(m_screen);
}

void Game::displayHUD(void){
    SDL_Rect rect={.x=m_screen->w/4, .y=30, .w=m_screen->w/2, .h=5};
    SDL_Rect rectPos={.x=rect.x+rect.w*((double)m_sapin.getPos()/m_map.getLength()), .y=20, .w=5, .h=20};
	SDL_FillRect(m_screen, &rect, SDL_MapRGB(m_screen->format, 100, 100, 100));
	SDL_FillRect(m_screen, &rectPos, SDL_MapRGB(m_screen->format, 0, 200, 0));
}

void Game::displaySapin(void){
    SDL_Surface *frame=m_sapin.getFrame();
    //SDL_Rect rect={.x=30, .y=m_screen->h-m_map.getFloorH()-frame->h};
    SDL_Rect rect={.x=30, .y=m_screen->h-frame->h-m_sapin.getPosY()};
    SDL_BlitSurface(frame, NULL, m_screen, &rect);
}

void Game::displayEnemy(void){
    int i;
    for(i=0; i<m_nbEnemy; i++){
        SDL_Surface *frame=m_enemy[i]->getFrame();
        SDL_Rect rect={.x=m_enemy[i]->getPos()-m_sapin.getPos()+30, .y=m_screen->h-frame->h-m_enemy[i]->getPosY()};
        if(rect.x+frame->w<0){
            enemyDelete(i);
            i--;
            continue;
        }
        SDL_BlitSurface(frame, NULL, m_screen, &rect);
    }
}

void Game::event(void){
    SDL_PollEvent(&m_event);
    switch(m_event.type)
    {
        case SDL_QUIT:
            m_quit=1;
            break;

        case SDL_KEYDOWN:
            switch(m_event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    m_quit=1;
                    break;
                case SDLK_UP:
                    m_sapin.jump();
                    break;
				case SDLK_x:
					m_sapin.shoot();
					break;
            }
            break;
    }
}

void Game::enemyDelete(int e){
    int i;
    m_physic.removeObjet(m_enemy[e]);
    for(i=e; i<m_nbEnemy-1; i++){
        m_enemy[i]=m_enemy[i+1];
    }
    m_nbEnemy--;
}
