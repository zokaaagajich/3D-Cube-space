#ifndef _GLOBALVARS_H_
#define _GLOBALVARS_H_

#define V .5
#define G 9.81
#define CUBE_SIZE 4
#define MAX_SHOOT 100

#include "bullet.h"

extern int MAX;

/* Promenljive za pucanje kockama */
extern bullet bullets[10];
extern int bfired;

/* Promenljive za inicijalne rotacije */
extern float angle_smallCubes;
extern float angle_BigCube;
extern float speed_BigCube;
extern float speed_smallCube;

/* Promeljive za inicijalnu animaciju */
extern float t_init;
extern float yt;

/* Promenljive za razlicite efekte */
extern float t_illusion;
extern float t_explosion;
extern float t_mix;

/* Promeljive za proveru da li su animacije pokrenute */
extern int animation_going;
extern int animation_y;
extern int animation_illusion;
extern int animation_explosion;
extern int animation_mix;

/* Promenljive za poziciju kamere */
extern float xpos, ypos, zpos;
/* Promenljive za cuvanje uglova rotacije oko x i y ose (xrot - gore dole, yrot - levo desno) */
extern float xrot, yrot;

/* Promenljive za funkcije za rad sa misom */
extern float mouse_x, mouse_y;
extern int on_mouse_left_down;

/* Promenljive za ekran */
extern float window_width, window_height;

#endif
