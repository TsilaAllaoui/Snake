#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include "snake.h"

using namespace std;

void draw_background(SDL_Surface * ecran, SDL_Surface * mur, SDL_Surface * score)
{
	SDL_Rect pos_score;
	pos_score.x = LONG / 2 - 64;
	pos_score.y = 0;
	SDL_BlitSurface(score, NULL, ecran, &pos_score);
	for (int i = 0; i < LONG / BLOC; i++)
	{
		for (int j = 2; j < LARG / BLOC; j++)
		{
			SDL_Rect pos;
			pos.x = i * BLOC;
			pos.y = j * BLOC;
			if (i == 0 || i == LONG / BLOC - 1)
				SDL_BlitSurface(mur, NULL, ecran, &pos);
			if (j == 2 || j == LARG / BLOC - 1)
				SDL_BlitSurface(mur, NULL, ecran, &pos);
		}
	}
	SDL_Flip(ecran);
}

void jeu(SDL_Surface * ecran)
{
	TTF_Init();
	TTF_Font *police = NULL;
	SDL_Color white = { 255, 255, 255 };
	police = TTF_OpenFont("BELL.TTF", 30);
	SDL_Surface *score, *fruit, *mur;
	mur = IMG_Load("wall.png");
	fruit = IMG_Load("fruit.png");
	SDL_Rect pos_fruit;
	pos_fruit.x = ((rand() % 18) + 1) * BLOC;
	pos_fruit.y = ((rand() % (20-2))+ 3) * BLOC;
	;
	Snake *s = NULL;
	s = (Snake *) malloc((100+ 1) * sizeof(Snake));
	int Long_actu = 1;
	s[0].Setxy(LONG / 2, LARG / 2);
	s[0].Setdirection(DROITE);
	SDL_Rect pos = s[0].Getxy();
	s[1].Setxy(pos.x - BLOC, pos.y);
	int condition = 1;
	SDL_Rect pos_score;
	pos_score.x = LONG / 2 - 40;
	pos_score.y = 0;
	while (condition)
	{
		s[1].affiche_body(ecran);
		s[0].affiche(ecran);
		draw_background(ecran, mur, score);
		SDL_Flip(ecran);

		SDL_Event debut;
		SDL_WaitEvent(&debut);
		switch (debut.type)
		{
		case SDL_KEYDOWN:
			switch (debut.key.keysym.sym)
			{
			case SDLK_UP:
				s[0].Setdirection(HAUT);
				condition = 0;
				break;
			case SDLK_DOWN:
				s[0].Setdirection(BAS);
				condition = 0;
				break;
			case SDLK_RIGHT:
				s[0].Setdirection(DROITE);
				condition = 0;
				break;
			case SDLK_LEFT:
				s[0].Setdirection(GAUCHE);
				condition = 0;
				break;
			}
			break;
		}
		SDL_Flip(ecran);
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	}
	char score_actu[50] = "";
	//test//
	string m = "638";
	for (int i=0;i<m.size();i++)
    	score_actu[i]=m[i];
	sprintf(score_actu, "Score :   %d", (Long_actu - 1) * 10);
	score = TTF_RenderText_Solid(police, score_actu, white);
	int finjeu = 0;
	while (!finjeu)
	{
		draw_background(ecran, mur, score);
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(fruit, NULL, ecran, &pos_fruit);
		s[0].eat(pos_fruit);
		Long_actu = s[0].Getlongueur();
		sprintf(score_actu, "Score :   %d", (Long_actu) * 10);
		score = TTF_RenderText_Solid(police, score_actu, white);
		draw_background(ecran, mur, score);
		for (int i = Long_actu + 1; i >= 1; i--)
		{
			s[i].move_body(s[i - 1]);
			s[i].affiche_body(ecran);
		}
		s[0].move(&finjeu, s, Long_actu);
		s[0].affiche(ecran);
		SDL_Flip(ecran);
		SDL_Delay(300);
	}
}