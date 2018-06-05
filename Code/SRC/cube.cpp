#include"vector.h"
#include "imageloader.h"
#include<GL/glut.h>

void cube(float bx2,float by2,float bz2, GLuint& _textureId) {

    glPushMatrix();

    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);

    gluLookAt(	x, 0.0f, z,
				x+lx, 0.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTranslatef(0.0f, 0.0f,-3.5);

       // Top face
       glBegin(GL_QUADS);              // Defined vertices in counter-clockwise order
      glColor3f(1.0f, 0.0f, 0.0f);     //ALL LINES YELLOW COLORED
      glVertex3f( bx2 ,by2, -bz2);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-bx2, by2, -bz2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-bx2, by2,  bz2);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f( bx2, by2,  bz2);
      glTexCoord2f(0.0f, 0.0f);
       glEnd();



      // Bottom face
       glBegin(GL_QUADS);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f( bx2, -by2,  bz2);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-bx2, -by2,  bz2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-bx2, -by2, -bz2);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f( bx2, -by2, -bz2);
      glTexCoord2f(0.0f, 0.0f);
       glEnd();

      // Back face (z = -1.0f)
       glBegin(GL_QUADS);
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex3f( bx2, -by2, -bz2);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-bx2, -by2, -bz2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-bx2,  by2, -bz2);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f( bx2,  by2, -bz2);
      glTexCoord2f(0.0f, 0.0f);
       glEnd();

      // Left face
       glBegin(GL_QUADS);
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex3f(-bx2,  by2,  bz2);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-bx2,  by2, -bz2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-bx2, -by2, -bz2);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-bx2, -by2,  bz2);
      glTexCoord2f(0.0f, 0.0f);
       glEnd();

      // Right face
       glBegin(GL_QUADS);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(bx2,  by2, -bz2);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(bx2,  by2,  bz2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(bx2, -by2,  bz2);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(bx2, -by2, -bz2);
      glTexCoord2f(0.0f, 0.0f);
       glEnd();  // End of drawing color-cube

      glDisable(GL_TEXTURE_2D);


   glPopMatrix();
   glFlush();
}
