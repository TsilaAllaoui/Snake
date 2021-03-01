#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "snake.h"

Snake::Snake()
{
	x = 0;
	y = LARG / 2;
	vitesse = 30;
	direction = DROITE;
	longueur = 0;
}

void Snake::move(int *finjeu, Snake * s, int Long_actu)
{
	int direction_actu = direction;
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			direction = HAUT;
			break;
		case SDLK_DOWN:
			direction = BAS;
			break;
		case SDLK_RIGHT:
			direction = DROITE;
			break;
		case SDLK_LEFT:
			direction = GAUCHE;
			break;
		case SDLK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		}
	}
	switch (direction)
	{
	case HAUT:
		{
			if (y == 3 * BLOC)
			{
				*finjeu = 1;
				break;
			}
			else if (direction_actu == BAS)
			{
				direction = BAS;
				// y += BLOC;
			}
			else
			{
				/*for (int i = 2; i <= Long_actu; i++)
				{
					if (y == s[i].Getxy().y)
					{
						*finjeu = 1;
						break;
					}
				}*/
				y -= BLOC;
				break;
			}
		}
	case BAS:
		{
			if (y == LONG)
			{
				*finjeu = 1;
				break;
			}
			if (direction_actu == HAUT)
			{
				direction = HAUT;
				y -= BLOC;
				break;
			}
			else
			{
				/*for (int i = 2; i <= Long_actu; i++)
				{
					if (y == s[i].Getxy().y)
					{
						*finjeu = 1;
						break;
					}
				}*/
				y += BLOC;
				break;
			}
		}
		break;
	case DROITE:
		if (x == LARG - BLOC * 4)
		{
			*finjeu = 1;
			break;
		}
		else if (direction_actu == GAUCHE)
		{
			direction = GAUCHE;
			x -= BLOC;
			break;
		}
		else
		{
			/*for (int i = 2; i <= Long_actu; i++)
				{
					if (x == s[i].Getxy().x)
					{
						*finjeu = 1;
						break;
					}
				}*/
			x += BLOC;
			break;
		}
	case GAUCHE:
		if (x == BLOC)
		{
			*finjeu = 1;
			break;
		}
		else if (direction_actu == DROITE)
		{
			direction = DROITE;
			x += BLOC;
			break;
		}
		else
		{
		/*	for (int i = 2; i <= Long_actu; i++)
				{
					if (x == s[i].Getxy().y)
					{
						*finjeu = 1;
						break;
					}
				}*/
			x -= BLOC;
			break;
		}
	}

}

void Snake::affiche(SDL_Surface * ecran)
{
	SDL_Surface *tete_haut, *tete_bas, *tete_gauche, *tete_droite;
	tete_haut = IMG_Load("tete_haut.png");
	tete_bas = IMG_Load("tete_bas.png");
	tete_gauche = IMG_Load("tete_gauche.png");
	tete_droite = IMG_Load("tete_droite.png");
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	switch (direction)
	{
	case HAUT:
		SDL_BlitSurface(tete_haut, NULL, ecran, &pos);
		break;
	case BAS:
		SDL_BlitSurface(tete_bas, NULL, ecran, &pos);
		break;
	case DROITE:
		SDL_BlitSurface(tete_droite, NULL, ecran, &pos);
		break;
	case GAUCHE:
		SDL_BlitSurface(tete_gauche, NULL, ecran, &pos);
		break;
	}
}

void Snake::affiche_body(SDL_Surface * ecran)
{
	tete = IMG_Load("body.png");
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_BlitSurface(tete, NULL, ecran, &pos);
}

SDL_Rect Snake::Getxy()
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

int Snake::Getdirection()
{
	direction = 0;
	return direction;
}

void Snake::move_body(Snake & s)
{
	SDL_Rect pos_tete;
	pos_tete = s.Getxy();
	x = pos_tete.x;
	y = pos_tete.y;
}

void Snake::Setxy(int a, int b)
{
	x = a;
	y = b;
}

void Snake::Setdirection(int a)
{
	direction = a;
}

int Snake::Getlength()
{
	return longueur;
}

void Snake::add_body()
{
	longueur++;
}

int Snake::Getlongueur()
{
	return longueur;
}

void Snake::eat(SDL_Rect & pos)
{
	if (x == pos.x && y == pos.y)
	{
		add_body();
		pos.x =((rand() % 18) + 1) * BLOC;
	pos.y = ((rand() % (20-2))+ 3) * BLOC;
	}
}