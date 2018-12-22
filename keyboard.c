#include <GL/glut.h>
#include <math.h>

#include "globalvars.h"
#include "keyboard.h"
#include "timers.h"
#include "bullet.h"

void on_keyboard(unsigned char key, int x, int y)
{
	switch(key) {
		case 27:
		/* Izlazak iz programa na ESC */
							exit(0);
							break;

		case 's':
		case 'S':
		/* Azuriranje vrednosti za rotaciju kamere po Y osi*/
							xrot -= 1;
							if (xrot < -360)
								xrot += 360;
							break;

		case 'w':
		case 'W':
		/* Azuriranje vrednosti za rotaciju kamere po X osi*/
							xrot += 1;
							if(xrot > 360)
								xrot -= 360;
							break;

		case 'a':
		case 'A':
		/* Azuriranje vrednosti za rotaciju kamere po Y osi */
							yrot += 1;
							if (yrot > 360)
								yrot -= 360;

							/* Azuriranje za fju on_mouse_movement */
							/* Zavisi od Pi jer imamo kruzne pravce, a ne koristim ugradjeno jer ce svaki put
									ugradjena fja dati neku novu zaokruzenu vrednost */
						  {
								float yrotrad;
								yrotrad = (yrot / 180 * 3.141592654f);
								xpos -= (float)(cos(yrotrad));
								zpos -= (float)(sin(yrotrad));
							}

							break;

    case 'd':
    case 'D':
		/* Azuriranje vrednosti za rotaciju kamere po X osi*/
							yrot -= 1;
							if (yrot < -360)
								yrot += 360;

								/* Zavisi od Pi jer imamo kruzne pravce, a ne koristim ugradjeno jer ce svaki put
									ugradjena fja dati neku novu zaokruzenu vrednost */
							{
								float yrotrad;
								yrotrad = (yrot / 180 * 3.141592654f);
								xpos += (float)(cos(yrotrad));
								zpos += (float)(sin(yrotrad));
							}

							break;

		case 'i':
		case 'I':
		/* Pokretanje efekta iluzije */
							if(!animation_illusion) {
								glutTimerFunc(TIMER_MS, on_timer_illusion, TIMER_ILLUSION);
								animation_illusion = 1;
							}
							break;
		case 'm':
		case 'M':
		/* Pokretanje efekta mix */
							if(!animation_mix) {
								glutTimerFunc(TIMER_MS, on_timer_mix, TIMER_MIX);
								animation_mix = 1;
							}
							break;

		case 'e':
		case 'E':
		/* Pokretanje efekta eksplozije */
							if(!animation_explosion){
								glutTimerFunc(TIMER_MS, on_timer_explosion, TIMER_EXPLOSION);
								animation_explosion = 1;
							}
							break;

		case 'r':
		case 'R':
		/* Reset */
							animation_going = 1;
							animation_illusion = 0;
							t_illusion = 0;
							animation_explosion = 0;
							t_explosion = 0;
							animation_mix = 0;
							t_mix = 0;
							glutPostRedisplay();
							break;

		case 'f':
		case 'F':
		/* Pucanje kockom */
							bullets[bfired++] = create_bullet(-90, -90, -90);
							break;

		case ' ':
		/* Pauziranje animacija na space */
							if(!animation_going){
								glutTimerFunc(TIMER_MS, on_timer_move, TIMER_MOVE);
									animation_going = 1;
									animation_illusion = 1;
									animation_explosion = 1;
									animation_mix = 1;
							}
							else {
								animation_going = 0;
								animation_illusion = 0;
								animation_mix = 0;
								animation_explosion = 0;
							}

							break;
	}
}

void on_keyboard_special(int key, int x, int y)
{
	float xrotrad, yrotrad;
	switch(key) {

		case GLUT_KEY_RIGHT:
		/* Ubrzava - efekat kao da ide unapred */
							angle_BigCube += 1.8f;
							angle_smallCubes += 1.9f;
							break;

		case GLUT_KEY_LEFT:
		/* Kao da ide unazad */
							angle_BigCube -= 3.8f;
							angle_smallCubes -= 3.9f;
							break;

		case GLUT_KEY_DOWN:
		/* Odaljavamo se od kocke */
		/* yrotrad je ugao za koji smo rotirali.. malo geometrije dobiju se formule */
							yrotrad = (yrot / 180 * 3.141592654f);
							xrotrad = (xrot / 180 * 3.141592654f);
							xpos -= (float)(sin(yrotrad));
							zpos += (float)(cos(yrotrad));
							ypos += (float)(sin(xrotrad));

							/* Ako smo dovoljno van kocke ubrzaj je */
							if(zpos >= -50) {
								speed_BigCube = 0.6f;
								speed_smallCube = 0.7f;
							}
							break;

		case GLUT_KEY_UP:
		/* Ulazimo u kocku */
						yrotrad = (yrot / 180 * 3.141592654f);
						xrotrad = (xrot / 180 * 3.141592654f);
						xpos += (float)(sin(yrotrad));
						zpos -= (float)(cos(yrotrad));
						ypos -= (float)(sin(xrotrad));

						/* Kad udjemo u nju usporavamo je - estetski razlog */
						if(zpos <= -50) {
							speed_BigCube = 0.2f;
							speed_smallCube = 0.3f;
						}
						break;
	}
}
