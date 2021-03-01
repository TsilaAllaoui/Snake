#ifndef SNAKE_H
#define SNAKE_H
#include <SDL/SDL.h>
#define BLOC 16
#define LONG 320
#define LARG 352

enum
{ HAUT, BAS, GAUCHE, DROITE, STOP };
class Snake
{
  private:
	int x, y, vitesse, direction,longueur;
	SDL_Surface *tete;
  public:
	  Snake();
	int Getlength();
	void move(int *finjeu,Snake *s,int Long_actu);
	void affiche(SDL_Surface * ecran);
	void affiche_body(SDL_Surface * ecran);
	SDL_Rect Getxy();
	int Getdirection();
	void move_body(Snake & s);
	void Setxy(int a, int b);
	void Setdirection(int a);
	void eat(SDL_Rect &pos);
    void add_body();
    int Getlongueur();

};


#endif