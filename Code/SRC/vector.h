#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>

extern float x,z,deltaAngle,deltaMove,lx,lz,angle;    //just declared here for using them in cube as well as main cpp files for lookat

class vect {
public:
	float x;
	float y;
	float z;
    vect();
	vect(float defaultVal);
	vect(float a, float b, float c);
	vect(const vect& a);
    vect& operator=(const vect &a);

	void normalize(); //!<  handles normalization of a vector.
    void scale(float a); //!< scales the vector by specified value.
	void add(const vect& a); //!< utility method for performing vector addition.
	void subtract(const vect& a); //!< utility method for performing vector subtraction
	float dot(const vect& a); //!< utility method for performing vector dot multiplication
	float mod(); //!< returns the magnitude of the vector
	void comp(float a, float b, float c);
    void comp(vect& a);
    void flaginv();
    bool gcheckmin(vect& a);
    bool gcheckmax(vect& a);

    };

#endif // VECTOR_H_
