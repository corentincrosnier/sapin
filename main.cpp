#include <SDL/SDL.h>
SDL_Surface *m_screen=SDL_SetVideoMode(1200, 500, 32, SDL_HWSURFACE);

#include "Game.h"

//SDL_Surface* Displayable::m_screen=SDL_SetVideoMode(1200, 500, 32, SDL_HWSURFACE);

int main(int argc, char **argv){
	SDL_Init(SDL_INIT_VIDEO);
//	SDL_Surface *screen=SDL_SetVideoMode(1200, 500, 32, SDL_HWSURFACE);
    if(!m_screen)
        return 0;
	srand(time(NULL));
    Game game(m_screen);

	SDL_WM_SetCaption("sapin", NULL);
	SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0, 0, 0));
    game.play();

    SDL_Quit();
    return 0;
}
