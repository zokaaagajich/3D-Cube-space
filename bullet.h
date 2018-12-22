#ifndef _BULLET_H
#define _BULLET_H

/* Struktura bullet koja cuva koordinate pravca za kocku */
typedef struct
{
	float x, y, z;
} bullet;

/* Funkcija za iscrtavanje kocke za "pucanje" */
void draw_bullet(bullet* b);
/* Funkcija za kreiranje promenljive strukture bullet */
bullet create_bullet(float x, float y, float z);

#endif
