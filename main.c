#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "globalvars.h"
#include "display.h"
#include "timers.h"
#include "keyboard.h"

int main(int argc, char ** argv)
{
	/* Inicijalizuje se GLUT. */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* Kreira se prozor. */
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D-Cube-Space");

	/* Najbolje je izabrati 10x10, odnosno ovo sto je po default-u
	jer su sve animacije pravljene bas za 10x10.
 	U suprotnom nece doci do izrazaja neke sitnice kao sto su:
		pozicija svetla.. */

	/* Ako je neko naveo vise argumenata gledacemo samo argv[1] sta je. */
	if(argc >= 2) {
		/* Ako je neko naveo van intervala postavi po default-u 10x10 matricu kocki. */
		if(atoi(argv[1])<=1 || atoi(argv[1])>15)
			MAX = 100;
		else MAX = 10*atoi(argv[1]);
	}
	else MAX = 100;

	/* Registruju se funkcije za obradu dogadjaja. */
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	glutSpecialFunc(on_keyboard_special);
	glutMotionFunc(on_mouse_movement);
	glutMouseFunc(on_mouse);
	glutReshapeFunc(on_reshape);
	glutIdleFunc(on_display);

	/* Ugaseno ali moze se ukljuciti da se vidi kako izgleda
	glutPassiveMotionFunc(on_mouse_passive_movement); */

	/* Inicijalizacija promenjljivih, svetla.. */
	initialize();
	/* Ulazi se u glavnu petlju. */
	glutMainLoop();
	return 0;
}
