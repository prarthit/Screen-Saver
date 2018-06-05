//Created by Mohan - 2016CSJ0019 AND Prarthit - 2016CSJ0027 on 19 Feb 2018
//Copyrights(c) Prarthit Mehra
//All Rights Reserved

#include<GL/glut.h>
#include"ball.h"
#include"vector.h"
#include "imageloader.h"
#include<math.h>
#include<iostream>
#include<unistd.h>

using namespace std;

#define bx 1.0
#define by 1.0
#define bz 1.0

//for reshape function
void reshaped(int,int );  //handles window resize
float ratioo;             //for aspect ratio and according to it all objects will be positioned
//till here

//for randinitball function
void randInitBalls();     //initializes positions of balls and obstacles

int numofballs;           //just keeping here but will be used everywhere these are number of balls given in argv or initially 5 in makefile

vector<ball> b;           //a vector for number of balls
vector<int> ball_num(4);  //a vector which has numbers at indexes i eg [0]=0,[1]=1,[2]=2... used to give threads the indexes of balls
vector<pthread_t> trd(4); //thread for handling each ball's translate function initially 4 but is resized later...

ball obstacle[10];        // 10 obstacles created
int obsnum[10];           //a vector which has numbers at indexes i eg [0]=0,[1]=1,[2]=2... used to give threads the indexes of obstacles
float change=0.8;         //for changing position of obstacles by decrementing it 0.4 look at code to understand
pthread_t trd_obs[10];    //thread for handling each obstacle's translate function

pthread_t col;            //thread for handling collision

void* transl(void *);     //function where thread will be called it will handle translate of all balls
void* translobs(void *);  //function where thread will be called it will handle translate of all obstacles
void* collision(void*);   //function which will handle all collisions
//till here

//for display function
void display();
void cube(float,float,float,GLuint&); //makes cube just declared here coz no cube.h file only cube.cpp which has this function

float lx=0.0f,lz=-1.0f;         // XZ position of the camera
float x=0.0f, z=0.000001f;      // the key states. These variables will be zero
float deltaMove = 0;        //when no key is being presses

void pressKey(int,int,int);   //when you press up/down key what it has to do
void releaseKey(int,int,int); //when you release up/down key it should stop moving
void computePos(float);       //compute positions of x and z after key being pressed

void shade_ball();            //for shading/lighting purposes(balls)
//till here

//for inputs
void keys(unsigned char,int ,int );  //a function which handles the inputs +/- and space and esc

vector<vect> old_vel(4);  //for storing old velocity of balls when u press space to pause and play

int flag = 0;             //for the spacebar function input keypress (pause/play)

vect max_vel(0.008);      //when you keep pressing + to increase speed and if any one ball reaches max_vel then + wont work
vect min_vel(0.000001);   //same of above goes here
//till here


void lookat(int,int,int);

//for textures
GLuint loadTexture(Image*);
void initRendering();
GLuint _textureId;
//till here


int main(int argc,char **argv)
{
    if(argc == 2)
        numofballs = atoi(argv[1]);     //atoi means argv to int

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(640,480);

    glutCreateWindow("SCREEN SAVER");

    glClearColor(0.0,0.0,0.0,0);

    initRendering();

    glutReshapeFunc(reshaped);

    randInitBalls();

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutKeyboardFunc(keys);

    glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glEnable(GL_DEPTH_TEST);
    glViewport(0,0,640,480);

    glutMainLoop();

}



void reshaped(int w,int h)
{
    ratioo = w*1.0/h;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(43, ratioo, 1, 10 );

    glMatrixMode(GL_MODELVIEW);
}


void* transl(void* p)
{
    int *temp;
    temp = (int *)p;
    while(true)
    {
        b[*temp].translate(ratioo);
        usleep(2000);
    }
}


void* translobs(void* s)
{
    int *temp1;
    temp1 = (int *)s;
    while(true)
    {
        obstacle[*temp1].obs_translate();
        usleep(2000);
    }
}


void randInitBalls()
    {
        mt19937 ran((random_device())());
        uniform_real_distribution<> xposGen(-bx+0.25, bx-0.25);
        uniform_real_distribution<> yposGen(-by+0.25, by-0.25);
        uniform_real_distribution<> zposGen(-bz+0.25, bz-0.25);

        uniform_real_distribution<> radGen(0.1, 0.3);
        uniform_real_distribution<> velGen(0.001, 0.003);
        uniform_real_distribution<> colorGen(0.1, 0.9);

        trd.resize(numofballs);
        ball_num.resize(numofballs);
        old_vel.resize(numofballs);


        for (int i = 0; i < numofballs; i++)
        {
            ball_num[i] = i;
            ball newb;

            newb.initball(xposGen, yposGen,zposGen, radGen, velGen, colorGen, ran);
            b.push_back(newb);
            pthread_create(&trd[i],NULL,&transl,(void *)&ball_num[i]);
        }

        for(int i=0;i<5;i++)
        {
            obstacle[i].obsball(ratioo,change);
            obstacle[i+5].obsball(-ratioo,change);
            change-=0.4;
        }

        for(int i=0;i<10;i++)
        {
            obsnum[i]=i;
            pthread_create(&trd_obs[i],NULL,&translobs,(void *)&obsnum[i]);
        }

        pthread_create(&col,NULL,&collision,NULL);

    }

void* collision(void *ag)
{
    bool m =true;
    while(m==true)
    {
        for(int i=0;i<numofballs;i++)
        {

            for(int j=i+1;j<numofballs;j++)
            {

                vect t(b[i].pos);
                t.subtract(b[j].pos);

                vect vel_a(b[j].vel);
                vect vel_b(b[i].vel);
                if(t.mod() <= (b[i].radius+b[j].radius))
                    {
                        t.normalize();
                        vect t1(t),t2(t),t3(t),t4(t);

                        float u1 = t.dot(vel_a);
                        float u2 = t.dot(vel_b);

                        float b1 = u2, b2 = u1;
                        t.scale(u1);
                        vel_a.subtract(t);
                        t1.scale(b1);
                        vel_a.add(t1);
                        t2.scale(u2);
                        vel_b.subtract(t2);
                        t3.scale(b2);
                        vel_b.add(t3);
                        vel_a.comp(b[j].vel);
                        vel_b.comp(b[i].vel);

                        vect f(b[j].pos);
                        t4.scale(0.2 + 0.001);
                        f.add(t4);
                        f.comp(b[i].pos);

                        vect temp(b[i].flag);
                        b[j].flag.comp(b[i].flag);
                        temp.comp(b[j].flag);

                    }
            }

            for(int k=0;k<10;k++)
            {
                vect t(b[i].pos);
                t.subtract(obstacle[k].pos);

                vect vel_a(b[i].vel);
                vect vel_b(b[i].vel);

                if(t.mod() <= (b[i].radius+obstacle[k].radius))
                {
                    t.normalize();
                    vect t4(t);
                    vect f(obstacle[k].pos);
                    t4.scale(0.2 + 0.001);
                    f.add(t4);
                    f.comp(b[i].pos);

                    b[i].flag.flaginv();

                }
            }

        }

    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if (deltaMove)
		computePos(deltaMove);

    cube(ratioo,by,bz,_textureId);


    for(int i=0;i<numofballs;i++)
    {
        glPushMatrix();

        glColor3f(b[i].R,b[i].G,b[i].B);

        shade_ball();

        glLoadIdentity();

        gluLookAt(	x, 0.0f, z,
				x+lx, 0.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

        glTranslatef(b[i].pos.x,b[i].pos.y,b[i].pos.z-3.5);

        glutSolidSphere(b[i].radius,100,100);

        glPopMatrix();


    }


    for(int i=0;i<5;i++)
    {
        glPushMatrix();

        glColor3f(0.0f,0.0f,0.0f);
        shade_ball();

        glLoadIdentity();

        gluLookAt(	x, 0.0f, z,
				x+lx, 0.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

        glTranslatef(ratioo,obstacle[i].pos.y,obstacle[i].pos.z-3.5);

        glutSolidSphere(obstacle[i].radius,100,100);

        glPopMatrix();
    }

    for(int i=5;i<10;i++)
    {
        glPushMatrix();

        glColor3f(0.0f,0.0f,0.0f);
        shade_ball();

        glLoadIdentity();

        gluLookAt(	x, 0.0f, z,
				x+lx, 0.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

        glTranslatef(-ratioo,obstacle[i].pos.y,obstacle[i].pos.z-3.5);

        glutSolidSphere(obstacle[i].radius,100,100);

        glPopMatrix();

    }

    glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);


        glutSwapBuffers();
        glFlush();
    }


void pressKey(int key, int xx, int yy) {

	switch (key) {

		case GLUT_KEY_UP :

		    if(x>=ratioo || x<=-ratioo || z<-3.4)
                break;

            deltaMove = 0.2f; break;

		case GLUT_KEY_DOWN :

		    if(x>=ratioo || x<=-ratioo || z>-0.000001)
                break;

            deltaMove = -0.2f; break;

        case GLUT_KEY_F5 :
            glutFullScreen();
            break;

        case GLUT_KEY_F4 :
            glutReshapeWindow(640,480);
            break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {

		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;

	}
}

void computePos(float deltaMove) {

	x += deltaMove * (0) * 0.1f;
	z += deltaMove * (-1) * 0.1f;
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB,                       //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,             //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("crate.bmp");
	_textureId = loadTexture(image);
	delete image;
}


void shade_ball()
{
    // Lighting set up
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	// Set lighting intensity and color
	GLfloat qaAmbientLight[]	= {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat qaDiffuseLight[]	= {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	GLfloat qaLightPosition[]	= {0.0f, 1.0f, -0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	glShadeModel(GL_FLAT);

	GLfloat qaGreen[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat qaLowAmbient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat qaFullAmbient[] = {1.0, 1.0, 1.0, 1.0};

	//Set, ambient, diffuse and specular lighting. Set ambient to 20%.
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
		glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
}


void keys(unsigned char key,int x,int y)
{

    if(key==27)
        exit(0);

    if(key==43 && flag!=1)
    {

        for(int i=0;i<numofballs;i++)
        {
            if(b[i].vel.gcheckmax(max_vel)==true)
                    break;

            b[i].vel.add(0.0001);
        }
    }

    if(key==45 && flag!=1)
    {
        for(int i=0;i<numofballs;i++)
        {
            if(b[i].vel.gcheckmin(min_vel)==true)
                    break;

            b[i].vel.subtract(0.00005);
        }
    }

    if(key==32 && flag==0)
    {
        for(int i=0;i<numofballs;i++)
        {
            b[i].vel.comp(old_vel[i]);
            b[i].vel.scale(0);
        }
        for(int i=0;i<10;i++)
        {
            obstacle[i].vel.scale(0);
        }
        flag = 1;
    }

    else if(key==32 && flag==1)
    {
        for(int i=0;i<numofballs;i++)
        {
            old_vel[i].comp(b[i].vel);
        }
        for(int i=0;i<10;i++)
        {
            obstacle[i].vel.comp(0.0,0.0,0.001);
        }
        flag = 0;
    }
}

