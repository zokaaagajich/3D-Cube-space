#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "bullet.h"
#include "globalvars.h"
#include "display.h"
#include "timers.h"

/* Inicijalizacija promenljivih */
float xpos = 0, ypos = 0, zpos = 0;
float xrot = 0, yrot = 0;

float mouse_x = 0, mouse_y = 0;
int on_mouse_left_down = 0;

float t_init = 0;
float yt = 0 ;
float t_illusion = 0;
float t_explosion = 0;
float t_mix = 0;

float angle_smallCubes = 0.0f;
float angle_BigCube = 0.0f;
float speed_BigCube = 0.6f;
float speed_smallCube = 0.7f;

bullet bullets[10];
int bfired = 0;

static float matrix[16];

void initialize(void)
{
  /* Obavlja se OpenGL inicijalizacija. */
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  /* Svetlost */

  /* Ukljucujemo ono sto je potrebno za svetlo */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* Ovo nam sluzi da se u obzir uzme i boja nasih kocki jer bez ovoga je teze namestiti ovakve
  boje preko svetlosti */
  glEnable(GL_COLOR_MATERIAL);

  /* Postavljamo poziciju svetla */
  float light_position[] = {MAX/2, 0, MAX*2, 0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  /* Ukljucimo two_side mode, meni se cini da izgleda lepse sa ovim..  */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

  /* Uslovi animacije koje se inicijalno pokrecu */
  /* Uslov za pocetak animacije pravljenja kocke sloj po sloj padajuci odozgo */
  if(!animation_y) {
		glutTimerFunc(TIMER_MS, on_timer_y, TIMER_Y);
		animation_y = 1;
	}

  /* Uslov za pocetak rotacije Velike kocke */
	if(!animation_going) {
		glutTimerFunc(TIMER_MS, on_timer_move, TIMER_MOVE);
		animation_going = 1;
	}

  /* Inicijalizacija matrice rotacije za mis */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}

void on_display(void)
{
  /* Postavlja se boja svih piksela na zadatu boju pozadine. */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* Inicijalizacija kamere */
  camera();

  /* Postavlja se vidna tacka. */
  gluLookAt(0, 0, 140,
        0, 0, 0,
        0, 1, 0);

  /* Primenjuje se matrica rotacije. */
  glPushMatrix();
	  glMultMatrixf(matrix);
	  /* Crtanje Velike kocke */
	  draw();
  glPopMatrix();

  /* Kreiramo kocke za pucanje */
  glPushMatrix();
    for(int i = 0; i < bfired; ++i) {
  	   draw_bullet(&bullets[i]);
    }
  glPopMatrix();

  /* Postavlja se nova slika u prozor. */
  glutSwapBuffers();
}

void on_reshape(int width, int height)
{
  window_width = width;
  window_height = height;
  /* Postavlja se viewport. */
	glViewport(0, 0, width, height);

  /* Postavljaju se parametri projekcije. */
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	gluPerspective(90, (float)width/(float)height, 1, 1500);

  glMatrixMode(GL_MODELVIEW);
}

void on_mouse_movement(int x, int y)
{
    /* Proveravamo razliku izmedju pocetnog x i poslednje x pozicije */
    int diff_x = x-mouse_x;
    /* Proveravamo razliku izmedju pocetnog y i poslednje y pozicije */
    int diff_y = y-mouse_y;

    /* Postavljamo mouse_x na trenutnu poziciju x */
    mouse_x = x;
    /* Postavljamo mouse_y na trenutnu poziciju y */
    mouse_y = y;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotatef(180 * (float) diff_x / window_width, 0, 1, 0);
        glRotatef(180 * (float) diff_y / window_height, 1, 0, 0);
        glMultMatrixf(matrix);

        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();
}


/* Ne pozivam ovu funkciju jer bolje radi bez nje, tj samo on_motion
  Sa passive varijantom moze da se pomera. Ukljuciti u main */
void on_mouse_passive_movement(int x, int y)
{
    /* Proveravamo razliku izmedju pocetnog x i poslednje x pozicije */
    int diff_x = x-mouse_x;
    /* Proveravamo razliku izmedju pocetnog y i poslednje y pozicije */
    int diff_y = y-mouse_y;

    /* Postavljamo mouse_x na trenutnu poziciju x */
    mouse_x = x;
    /* Postavljamo mouse_y na trenutnu poziciju y */
    mouse_y = y;

    /* Postavlja xrot i yrot u zavisnosti od razlike za x i y pozicije */
    xrot += (float) diff_y;
    yrot += (float) diff_x;
}

void on_mouse(int button, int state, int x, int y) {
   mouse_x = x;
   mouse_y = y;
}

void camera(void)
{
  /* Rotacija kamere po X-osi */
  glRotatef(xrot, 1.0, 0.0, 0.0);
  /* Rotacija kamere po Y-osi */
	glRotatef(yrot, 0.0, 1.0, 0.0);
  /* Transliramo ekran u poziciju kamere */
  glTranslatef(-xpos, -ypos, -zpos);
}

void draw(void)
{
  /* Rotiranje Velike kocke oko svih osa odvojeno, dobijamo efekat
  da se malo rotira u jednu stranu, pa u drugu.. */
  glRotatef(angle_BigCube, 0, 0, 1);
	glRotatef(angle_BigCube, 0, 1, 0);
	glRotatef(angle_BigCube, 1, 0, 0);

  /* Trostruka petlja za pravljenje Velike kocke od malih kocki */
	for(int x = 0; x < MAX; x+=10) {
		for (int y = 0; y < MAX; y+=10) {
			    glPushMatrix();

          /* Inicijalna animacija (redjanje red po red kocki) */
    			yt = y + V*y*t_init - G*t_init*t_init/2.0;
    		  if(t_init > 0 && yt > 0)
    				glTranslatef(0, MAX*log(yt), 0);

		      for(int z = 0; z < MAX; z+=10) {
				    glPushMatrix();

  				/* Vracanje u koorinatni pocetak */
  				glTranslatef(-MAX/2, -MAX/2, -MAX/2);
  				glTranslatef(x, y, z);

  				/* Rotacija pojedinacnih malih kocki */
  				glRotatef(angle_smallCubes, 0, 0, 1);
  				glRotatef(angle_smallCubes, 0, 1, 0);
  				glRotatef(angle_smallCubes, 1, 0, 0);

          /* Postavljamo boju u zavisnosti od koordinata => lepe razlicite boje + efekat prelivanja boja */
  				glColor3f((float)x/MAX, (float)y/MAX, (float)z/MAX);

          /* Animacija iluzije  */
          glTranslatef(85*sin(t_illusion/50)*sin(x), 85*sin(t_illusion/50)*sin(y), 85*sin(t_illusion/50)*sin(z));

          /* Animacija eksplozije */
          glTranslatef(MAX/2*t_explosion*cos(x), MAX/2*t_explosion*cos(y), MAX/2*t_explosion*cos(z));

          /* Animacija mix */
          glTranslatef(25*sin(t_mix/3)*cos(x/2), 25*sin(t_mix/3)*cos(y/2), 25*sin(t_mix/3)*cos(z/2));

          /* Kreiranje pojedinacne male kocke */
          glutSolidCube(CUBE_SIZE);
  				glPopMatrix();
			}
			glPopMatrix();
		}
	}

  // Ako zelite jos ludje animacije
  //  angle_smallCubes += speed_smallCube;

}
