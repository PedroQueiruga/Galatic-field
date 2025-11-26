// System Headers
//#include <iostream.h>
//#include <strstream.h>
#include <math.h>
#include <time.h>
#include <random>
#include <fstream>

#include "types.h"

#ifndef MATHEMATICS_H_INCLUDED
#define MATHEMATICS_H_INCLUDED

class Mathematics
{
 private:
 	float a,b,c;
 	//Types::float_precision vpar[3],vper[3],vec1[3],vec2[3];
  	//Types::float_precision&;
  	
  	std::mt19937 engine;
  	std::uniform_real_distribution<double> dist;
    
 public:

  //! Constructor of the class.
  Mathematics ( );

  //! Destructor of the class.
  ~Mathematics ( );
  
  //Vector product
  void VecProd(Types::float_precision prod[3],const Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //Modulus
  Types::float_precision Mod(const Types::float_precision vec[3]);
  
  //Normalization
  void Norm(Types::float_precision versor[3], const Types::float_precision vector[3]);
  
  //Scalar product
  Types::float_precision ScalarProd(const Types::float_precision vec1[3],const Types::float_precision vec2[3]);
  
  //Angle between vectors
  Types::float_precision Angle2Vec(const Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //parallel vector and perpendicular(pe=perpendicular/pa=parallel)
  void Projections(Types::float_precision vpar[3],Types::float_precision vper[3],const Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //Cart2Esf: Makes the coordinate change cartesian to spherical
  
  void Cart2Esf(Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //Cart2Cyl: Makes the coordinate change cartesian to cylindrical
  
  void Cart2Cyl(Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //Cyl2Cart: Makes the coordinate change cylindrical to cartesian
  
  void Cyl2Cart(Types::float_precision vec1[3], const Types::float_precision vec2[3]);
  
  //Esf2Cart: Makes the coordinate change spherical to cartesian
  
  void Esf2Cart(Types::float_precision vec1[3], const Types::float_precision vec2[3], const Types::float_precision esf[3]);
  
  //random: Sorties a random number between 0 and 1 for a variable
  
  Types::float_precision random();
  
  //Rotation in X: The first term is the rotate magnetic field, the second is the original field.
  
  void rotationX(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta);
  
  //Rotation in Y:
  
  void rotationY(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta);
  
  //Rotation in Z:

  void rotationZ(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta);
  
  //Calculating the angle between a vector and axis x,y,z:
  
  Types::float_precision angleX(const Types::float_precision vec1[3]);
  
  Types::float_precision angleY(const Types::float_precision vec1[3]);
  
  Types::float_precision angleZ(const Types::float_precision vec1[3]);
};


#endif // MATHEMATICS_H_INCLUDED





