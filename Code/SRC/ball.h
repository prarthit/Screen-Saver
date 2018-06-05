#ifndef ball_h
#define ball_h
#include"vector.h"
#include <random>
using namespace std;

typedef uniform_real_distribution<> ud;

class ball
{
    public :
        vect pos,vel,flag;
        float radius, R,G,B;

        void translate(float);
        void obs_translate();
        void obsball(float,float);
        void initball(ud& xposGen, ud& yposGen,ud& zposGen, ud& radGen, ud& velGen, ud& colorGen, mt19937& ran);
};

#endif // _declares_h
