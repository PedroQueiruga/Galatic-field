// System Headers
//#include <iostream.h>
//#include <strstream.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "types.h"

class Physics
{
 private:
  //Types::float_precision& ;
    
 public:
  //! Constructor of the class.
  Physics ( );

  //! Destructor of the class.
  ~Physics ( );
  
  //declaration Lorentz
  void FLorentz(Types::float_precision F[3], const Types::float_precision& q, const Types::float_precision v[3], const Types::float_precision B[3]);
  
  //declaration velocity
  void Velocity(Types::float_precision v[3],const Types::float_precision v0[3],const Types::float_precision a[3],const Types::float_precision& t);
  
  //declaration Trajectory
  void Trajectory(Types::float_precision r[3],const Types::float_precision r0[3],const Types::float_precision v0[3],const Types::float_precision a[3],const Types::float_precision& t);
  
  //Angular velocity

  void Angvelocity(Types::float_precision& w,const Types::float_precision& q,const Types::float_precision& B,const Types::float_precision& m);

  //Moviment period

  void period(Types::float_precision& T,const Types::float_precision& w);

  //Larmor Radius

  void Larmor(Types::float_precision& rL,const Types::float_precision& m,const Types::float_precision& q,const Types::float_precision& vmod,const Types::float_precision& bmod);
  
  //pitch angle
  
  void Pitch(const Types::float_precision vper[3],const Types::float_precision vpar[3]);
  
  //Relativistic
  
  void Relat(Types::float_precision& m,const Types::float_precision& m_0,const Types::float_precision v[3]);
  
  //Galactic magnetic field model
  
  void GalacticASS(Types::float_precision BG[3],const Types::float_precision r[3]);
  
  //Galactic magnetic field model
  
  void GalacticBSS(Types::float_precision BG[3],const Types::float_precision r[3]);
  
  //Energy to relativistic velocity
  
  void Ener2vel(const Types::float_precision& E, Types::float_precision& modv, const Types::float_precision& c, const Types::float_precision& m);
  
  //Function gamma
  
  Types::float_precision gammafunc(const Types::float_precision& vmod,const Types::float_precision& c);
  
  //Turbulence
  
  void turbulence(Types::float_precision BGT[3], const Types::float_precision BG[3]);
  
  //Galatic Mapping (xy)
  
  void mappingxy(Types::float_precision& posx,Types::float_precision& posy,int model);
  
  //Galatic Mapping circular
  
  void mappingcircular(Types::float_precision& radiusG,int thetaG, int model);
  
  //Relativistic aceleration
  
  void accelerationRelativity(Types::float_precision a[3], const Types::float_precision F[3], const Types::float_precision v[3], const Types::float_precision& m_0);
  
};

#endif // PHYSICS_H_INCLUDED
