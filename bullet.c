#include "bullet.h"
#include "globalvars.h"
#include <GL/glut.h>
#include <stdio.h>

void draw_bullet(bullet* b)
{
	glDisable(GL_LIGHTING);
	//fprintf(stderr, "%f %f %f\n", b->x, b->y, b->z);
	glPushMatrix();
		glColor3f(0.8627451,0.07843137,0.23529412);
		/* Rotacije velike kocke */
		glRotatef(angle_BigCube, 1, 0, 0);
		/*Translacija tako da kocka sa vremenom nestane */
		glTranslatef(-7*b->x, -7*b->y, -7*b->z);
		/* Odredjujemo pravac */
		b->x += 1;
		b->y += 1;
		b->z += 1;
		glutSolidCube(30);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

bullet create_bullet(float x, float y, float z)
{
	bullet b = {.x = x, .y = y, .z = z};
	return b;
}
