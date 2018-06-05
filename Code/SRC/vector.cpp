#include"vector.h"
#include<iostream>
using namespace std;

vect::vect()
{
    x = y = z = 0;
}


vect::vect(float defaultVal)
{
    x = y = z = defaultVal;
}


vect::vect(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}


vect::vect(const vect& a)
{
    x = a.x;
    y = a.y;
    z = a.z;
}

void vect::normalize()
{
    float tmp = sqrt(x * x + y * y + z * z);
    if(tmp == 0)
        return;
    x /= tmp;
    y /= tmp;
    z /= tmp;
}


void vect::scale(float a)
{
    x *= a;
    y *= a;
    z *= a;
}


void vect::add(const vect& a)
{
    x += a.x;
    y += a.y;
    z += a.z;
}


void vect::subtract(const vect& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
}


float vect::dot(const vect& a)
{
    return (x * a.x + y * a.y + z * a.z);
}


float vect::mod()
{
    return sqrt(x * x + y * y + z * z);
}


void vect::comp(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}


void vect::comp(vect& a)
{
    a.x = x;
    a.y = y;
    a.z = z;
}

float f(float a)
    {
        if(a == 0)
            return 1;
        else
            return 0;
    }

void vect::flaginv()
{

    x = f(x);
    y = f(y);
    z = f(z);
}

bool vect::gcheckmax(vect& a)
{
    if(x>=a.x || y>=a.y || z>=a.z)
        {return true;}
    else
        {return false;}
}

bool vect::gcheckmin(vect& a)
{
    if(x<=a.x || y<=a.y || z<=a.z)
        {return true;}
    else
        {return false;}
}
