#include "globalvars.h"
#include "bullet.h"

int MAX;

/* Promenljive za pucanje kockama */
bullet bullets[10];
int bfired;

/* Promenljive za inicijalne rotacije */
float angle_smallCubes;
float angle_BigCube;
float speed_BigCube;
float speed_smallCube;

/* Promeljive za inicijalnu animaciju */
float t_init;
float yt;

/* Promenljive za razlicite efekte */
float t_illusion;
float t_explosion;
float t_mix;

/* Promeljive za proveru da li su animacije pokrenute */
int animation_going;
int animation_y;
int animation_illusion;
int animation_explosion;
int animation_mix;

/* Promenljive za poziciju kamere */
float xpos, ypos, zpos;
/* Promenljive za cuvanje uglova rotacije oko x i y ose (xrot - gore dole, yrot - levo desno) */
float xrot, yrot;

/* Promenljive za funkcije za rad sa misom */
float mouse_x, mouse_y;
int on_mouse_left_down;

/* Promenljive za ekran */
float window_width, window_height;
