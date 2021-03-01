
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "jeu.h"
#include "snake.h"
int main(int argc, char *argv[])
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *ecran, *start[3], *gameover;
	ecran = SDL_SetVideoMode(LONG, LARG, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	start[0] = IMG_Load("start1.png");
	start[1] = IMG_Load("start2.png");
	start[2] = IMG_Load("start3.png");
	gameover = IMG_Load("gameover.png");
	int rejoue = 0;
	while (!rejoue)
	{
		int debut = 0;
		SDL_Event event;
		while (!debut)
		{
			SDL_Rect pos;
			pos.x = 0;
			pos.y = LARG - 320;
			SDL_PollEvent(&event);
			for (int i = 0; i < 3; i++)
			{
				SDL_BlitSurface(start[i], NULL, ecran, &pos);
				SDL_Flip(ecran);
				SDL_Delay(300);
			}
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					debut = 1;
					break;
				}
			}
		}
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

		jeu(ecran);

		SDL_Rect pos;
		pos.x = 0;
		pos.y = LARG - 320;
		SDL_BlitSurface(gameover, NULL, ecran, &pos);
		SDL_Event event1;
		SDL_Flip(ecran);
		int redo = 0;
		while (!redo)
		{
			SDL_PollEvent(&event1);
			{
				switch (event1.type)
				{
				case SDL_QUIT:
					return 0;
					break;
				case SDL_KEYDOWN:
					{
						switch (event1.key.keysym.sym)
						{
						case SDLK_SPACE:
							redo = 1;
							rejoue = 0;
							break;
						case SDLK_ESCAPE:
							redo = 1;
							rejoue = 1;
							break;
						}
					}
				}
			}
		}
	}
}