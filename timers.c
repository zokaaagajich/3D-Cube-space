#include <GL/glut.h>
#include <stdio.h>
#include "globalvars.h"
#include "timers.h"

int animation_going = 0;
int animation_y = 0;
int animation_illusion = 0;
int animation_explosion = 0;
int animation_mix = 0;

/* Tajmer za animiranje inicijalnih rotacija */
void on_timer_move(int value)
{
	if(value != TIMER_MOVE)
		return;

	angle_BigCube += speed_BigCube;
	angle_smallCubes += speed_smallCube;

	/* Teramo da se ponovo iscrta */
	glutPostRedisplay();

	if(animation_going)
		glutTimerFunc(TIMER_MS, on_timer_move, TIMER_MOVE);
}

/* Tajmer za animiranje iluzije */
void on_timer_illusion(int value)
{
	if(value != TIMER_ILLUSION)
		return;

	t_illusion += 0.2;

	/* Teramo da se ponovo iscrta */
	glutPostRedisplay();

	if(animation_illusion)
		glutTimerFunc(TIMER_MS, on_timer_illusion, TIMER_ILLUSION);
}

/* Tajmer za animiranje eksplozije */
void on_timer_explosion(int value)
{
	if(value != TIMER_EXPLOSION)
		return;

	t_explosion += 0.2;

	/* Teramo da se ponovo iscrta */
	glutPostRedisplay();

	if(animation_explosion)
		glutTimerFunc(TIMER_MS, on_timer_explosion, TIMER_EXPLOSION);
}


/* Tajmer za inicijalnu animaciju pravljenja kocke */
void on_timer_y (int value)
{
	if(value != TIMER_Y)
		return;

	t_init += 0.2;

	/* Kada najvisi sloj padne na svoje mesto zavrsava se */
	if(MAX + V*MAX*t_init - G*t_init*t_init/2.0 <= 0){
		t_init = 0;
		yt = 0;
		animation_y = 0;
	}

	/* Teramo da se ponovo iscrta */
	glutPostRedisplay();

	if(animation_y)
		glutTimerFunc(TIMER_MS, on_timer_y, TIMER_Y);
}

void on_timer_mix(int value)
{
	if(value != TIMER_MIX)
		return;

	t_mix += 0.2;

	/* Teramo da se ponovo iscrta */
	glutPostRedisplay();

	if(animation_mix)
		glutTimerFunc(TIMER_MS, on_timer_mix, TIMER_MIX);
}
