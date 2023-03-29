// System Headers
//#include <iostream.h>
//#include <strstream.h>
#include <math.h>

class Mathematics
{
 private:
 	float a,b,c;
 	double vpar[3],vper[3],vec1[3],vec2[3];
  	//double ;
    
 public:
	#define pi 3.141592654
	#define rad2deg (180./pi)

  //! Constructor of the class.
  Mathematics ( );

  //! Destructor of the class.
  ~Mathematics ( );
  
  //Vector product
  double VecProd(double prod[3], double vec1[3], double vec2[3]);
  
  //Normalization
  void Norm(double versor[3], double vector[3]);
  
  //Modulus
  double Mod(double vec[3]);
  
  //Scalar product
  double ScalarProd(double vec1[3],double vec2[3]);
  
  //Angle between vectors
  double Angle2Vec(double vec1[3], double vec2[3]);
  
  //parallel vector and perpendicular(pe=perpendicular/pa=parallel)
  void Projections(double vpar[3],double vper[3],double vec1[3],double vec2[3]);
  
  //Cart2Esf: Makes the coordinate change cartesian to spherical
  
  void Cart2Esf(double vec1[3], double vec2[3]);
  
  //Cart2Cyl: Makes the coordinate change cartesian to cylindrical
  
  void Cart2Cyl(double vec1[3], double vec2[3]);
  
  //Cyl2Cart: Makes the coordinate change cylindrical to cartesian
  
  void Cyl2Cart(double vec1[3], double vec2[3]);
  
  //Esf2Cart: Makes the coordinate change spherical to cartesian
  
  void Esf2Cart(double vec1[3], double vec2[3], double esf[3]);
 
};








