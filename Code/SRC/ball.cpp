#include<GL/glut.h>
#include"ball.h"
#include<stdlib.h>
#include<iostream>

#define bx 1.0
#define by 1.0
#define bz 1.0

using namespace std;

void ball :: initball(ud& xposGen, ud& yposGen,ud& zposGen, ud& radGen, ud& velGen, ud& colorGen, mt19937& ran)
{
    flag.x = 0;
    flag.y = 0;
    flag.z = 0;
    radius = 0.1;
    R = colorGen(ran);
    G = colorGen(ran);
    B = colorGen(ran);
    vel.x = velGen(ran);
    vel.y = velGen(ran);
    vel.z = velGen(ran);
    pos.x = xposGen(ran);
    pos.y = yposGen(ran);
    pos.z = zposGen(ran);
}


void ball :: translate(float rat)
{
    if(flag.y==0)
    {
        pos.y+=vel.y;
        if(pos.y>by-radius)
            flag.y=1;
    }
    else
    {
        pos.y-=vel.y;
        if(pos.y<-by+radius)
            flag.y=0;
    }
    if(flag.x==0)
    {
        pos.x+=vel.x;
        if(pos.x>rat-radius)
            flag.x=1;
    }
    else
    {
        pos.x-=vel.x;
        if(pos.x<-rat+radius)
            flag.x=0;
    }

    if(flag.z==0)
    {
        pos.z+=vel.z;
        if(pos.z>bz-radius)
            flag.z=1;
    }
    else
    {
        pos.z-=vel.z;
        if(pos.z<-bz+radius)
            flag.z=0;
    }
}

void ball :: obsball(float x,float z)
{
    flag.x = 0;
    flag.y = 0;
    flag.z = 0;
    radius = 0.1;
    R = 0.0f;
    G = 0.0f;
    B = 0.0f;
    vel.x = 0.0f;
    vel.y = 0.0f;
    vel.z = 0.001f;
    pos.x = x;
    pos.y = 0.0f;
    pos.z = z;

}

void ball :: obs_translate()
{
    pos.z+=vel.z;
    if(pos.z>bz+radius)
        pos.z=(-1.0f);
}
