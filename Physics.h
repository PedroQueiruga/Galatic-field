// System Headers
//#include <iostream.h>
//#include <strstream.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
class Physics
{
 private:
  //double ;
    
 public:
  //! Constructor of the class.
  Physics ( );

  //! Destructor of the class.
  ~Physics ( );
  
  //declaration Lorentz
  float FLorentz(double F[3], double q, double v[3], double B[3]);
  
  //declaration velocity
  float Velocity(double v[3],double v0[3],double a[3],double t);
  
  //declaration Trajectory
  float Trajectory(double r[3],double r0[3],double v0[3],double a[3], double t);
  
  //Angular velocity

  double Angvelocity(double w,double q, double b, double m);

  //Moviment period

  double period(double T,double w);

  //Larmor Radius

  double Larmor(double rL, double m, double q, double vmod, double bmod);
  
  //pitch angle
  
  double Pitch(double vper[3], double vpar[3]);
  
  //Variable field

  void VarB(double B[3],double B0[3],double r[3],double rL);
  
  //dipole field
  
  void Dip(double BD[3], double r[3]);
  
  //Relativistic
  
  double Relat(double m, double m_0, double v[3]);
  
  //Galactic magnetic field model
  
  void Galactic(double BG[3], double r[3]);
  
  //Energy to moment relativistic
  
  double Ener2moment(double E, double modp,double c, double m);
  
  //Sorting moment
  
  void SortMoment(double modp,double m,double p[3]);
  
  //Energy to relativistic velocity
  
  double Ener2vel(double E, double modv,double c, double m);
  
  //Sorting velocity
  
  void SortVel(double modp,double m,double p[3]);

  //Kinetic Enerygy of the particle
  
  void kineticEnergy(double K,double modv, double m);
  
  //Material magnetic rigidity
  
  void rigidity(double Ri,double modB, double rL);
  
  //Function gamma
  
  double gammafunc(double vmod, double c);

  
};









