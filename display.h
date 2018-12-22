#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <GL/glut.h>

/* Deklaracije callback funkcija. */
void on_display(void);
void on_reshape(int width, int height);
void on_mouse_movement(int x, int y);
void on_mouse_passive_movement(int x, int y);
void on_mouse(int button, int state, int x, int y);

/* Inicijalizacija */
void initialize(void);
/* Inicijalizacija kamere */
void camera(void);
/* Crtanje objekta odnosno kocki */
void draw(void);

#endif
