//Physics.cc

// System Headers:
#include <stdlib.h>
#include <stdio.h>

// Local Headers:
#include "Physics.h"
#include "Mathematics.h"

// Constructor
Physics::Physics ( )       
{
  
}

// Destructor
Physics::~Physics ( )
{
        
}

//Lorentz force
float Physics::FLorentz(double F[3], double q, double v[3], double B[3])
{
	
	Mathematics * Math = new Mathematics();
	double prod[3];
	Math->VecProd(prod,v,B);
	
	for(int i=0;i<=2;i++) F[i]=q*prod[i];
	
	
  return 0;
}
//Colocar a saida primeiro / t:Intervalo de tempo

//Velocity
float Physics::Velocity(double v[3],double v0[3],double a[3],double t)
{
  Mathematics * Math = new Mathematics();
  int i,k;
  double v2[3];
  
  //printf(" v0=(%.6e,%.6e,%.6e) a=(%.3e,%.3e,%.3e) t=%.3e \n",v0[0],v0[1],v0[2],a[0],a[1],a[2],t);
  
  for(i=0;i<=2;i++) {
	  v[i]=v0[i]+(a[i]*t);
  } 

  double vv=Math->Mod(v); 
  //printf(" v=(%.6e,%.6e,%.6e), modv=%.12e\n",v[0],v[1],v[2],vv);
   
  Math->Norm(v2,v); 
  //printf(" v/vv=(%.6e,%.6e,%.6e), mod(v/vv)=%.12e \n",v[0]/vv,v[1]/vv,v[2]/vv,sqrt((v[0]*v[0]+v[1]*v[1]+v[2]*v[2])/(vv*vv)));
  //printf(" v2  =(%.6e,%.6e,%.6e), mod(v2)=%.12e \n",v2[0],v2[1],v2[2],sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]));
  
  double v0n=Math->Mod(v0); 
		
  for(k=0;k<=2;k++) v[k]=v2[k]*v0n;
  //printf(" v=(%.9e,%.9e,%.9e) \n\n",v[0],v[1],v[2]);
 
  return 0;
}

//Particle trajectory
float Physics::Trajectory(double r[3],double r0[3],double v0[3],double a[3], double t)
{
	
	
  for(int i=0;i<=2;i++) r[i]=r0[i]+v0[i]*t+0.5*(a[i]*t*t);
  
  
  return 0;
}

//Angular velocity

double Physics::Angvelocity(double w,double q, double b, double m)
{
	Mathematics * Math = new Mathematics();
	//double b;
	//b=Math->Mod(B);
	w=(q*b)/m;
	
	
  return w;
}

//Moviment period

double Physics::period(double T,double w)
{	
	
	T=(2*pi)/w;
	
  return T;
}

//Larmor Radius

double Physics::Larmor(double rL, double m, double q, double vmod, double bmod){
	
	Mathematics * Math = new Mathematics();
	//double b,vmod2;
	
	//b=Math->Mod(B);
	//vmod2=Math->Mod(v);	
	rL=(m*vmod)/(q*bmod);
	
	return rL;
}

//Pitch angle

double Physics::Pitch(double vper[3],double vpar[3]){
	
	Mathematics * Math = new Mathematics();
	double vmodper,vmodpar, angle;
	
	vmodpar=Math->Mod(vpar);
	vmodper=Math->Mod(vper);
	
	angle=atan(vmodper/vmodpar);
	
	/*printf("vmodpar=%.3e ",vmodpar);
	printf("vmodper=%.3e ",vmodper);
	
	*/
	
	//printf("angle=%.3e \n",angle);
	
	return angle;

}

//Variable field

void Physics::VarB(double B[3],double B0[3],double r[3],double rL){
	
	Mathematics * Math = new Mathematics();
	int i,k;
	double rmod,r1,rb;//r1 fator para diminuir o rmod
	double modB,modB0; 
	
	r1=0.0001*rL;
	rb=100000;
	
	rmod=Math->Mod(r);
	modB0=Math->Mod(B0);	
	
	//printf("\n  r=%.3e, B0=%.3e, ",rmod,modB0);
		
	for(k=0;k<=2;k++) B[k]=B0[k];		
	if(rmod>1){
		for(k=0;k<=2;k++) B[k]=((rb*B0[k]*r1)/rmod);
	}
	modB=Math->Mod(B);	
	//printf("B=%.9e \n",modB);	
	
//dipole field
}


void Physics::Dip(double BD[3], double r[3]){
	
	//BE:Campo dipolar em coordenadas esféricas, E:Conversão do r para esféricas, BD:Campo dipolar em coordenadas cartesianas
	
	Mathematics * Math = new Mathematics();
	int k;
	double E[3],BE[3],mi0=12.5663706143592*pow(10.0,-7),mi=8.00*pow(10.0,22);
	double r1=7*pow(10.0,6);
	
	Math->Cart2Esf(E,r);
	
//	for(k=0;k<=2;k++) E[k]=vec1[k];
	//printf("r=%.6e phi=%.6e theta=%.6e\n",E[0],E[1],E[2]);
	
	//calculando o campo dipolar em coordenadas esféricas:
	
	BE[0]=(mi0*mi*(cos(E[2])))/(2*pi*E[0]*E[0]*E[0]);
	
	BE[1]=0;
	
	BE[2]=(mi0*mi*(sin(E[2])))/(4*pi*E[0]*E[0]*E[0]);
	
	//printf("BEX=%.6e BEY=%.6e BEZ=%.6e\n",BE[0],BE[1],BE[2]);
	
	//Voltando o campo dipolar para coordenadas cartesianas:
	
	BD[0]=(BE[2]*cos(E[2])+BE[0]*sin(E[2]))*cos(E[2]);
	
	BD[1]=(BE[2]*cos(E[2])+BE[0]*sin(E[2]))*sin(E[2]);
	
	BD[2]=BE[0]*cos(E[2])-BE[2]*sin(E[2]);
	
	//printf("BDX=%.6e BDY=%.6e BDZ=%.6e\n",BD[0],BD[1],BD[2]);
	
}
	
double Physics::Relat(double m, double m_0, double v[3]){

	Mathematics * Math = new Mathematics();
	
	
	double gamma,vtmod;
	double c=3*pow(10,8);
	
	vtmod=Math->Mod(v);
	
	//printf("vtmod=%.4e \n",vtmod);
	//printf("c=%.4e \n",c);
	
	gamma=gammafunc(vtmod,c);
	
//	gama=1/sqrt(1-(vtmod*vtmod)/(c*c));
	
//	printf("gama=%.4e \n",gama);
	//printf("m_0=%.4e \n",m_0);
	
	m=m_0*gamma;
	
	//printf("mr=%.4e \n",mr);
	
	return m;
		
}

void Physics::Galactic(double BG[3],double r[3]){
	
	
	Mathematics * Math = new Mathematics();
	int k;
	double p[3], BC[3];
	double Bsp, B0p;
	
	//constants definition:
	
	double xi0=3.25539*pow(10.0,20), r0=2.623*pow(10.0,20),rho1=6.171*pow(10.0,19);
	double z1=9.257*pow(10.0,18),z2=1.234*pow(10.0,20);
	double beta=-5.67, P=-0.174533;
	
	//P is in radians;
	
	//Convert from cartesian to polar coordinates:
	//r[0]=x,r[1]=y,r[2]=z --> p[0]=rho,p[1]=theta,p[2]=z
	
	Math->Cart2Cyl(p,r);
	
	//printf("r=%.6e, theta=%.6e, z=%.6e \n",p[0],p[1],p[2]);
	
	//Calculating the ASS or the BSS (just need to uncheck):
	
	B0p=((3*r0)/p[0])*tanh(p[0]/rho1)*tanh(p[0]/rho1)*tanh(p[0]/rho1)*pow(10.0,-10); // is in Tesla
	
	//printf("B0p=%.6e\n",B0p);
	
	//ASS:
	//Bsp=B0p*cos(p[1]-beta*log(p[0]/xi0))*cos(p[1]-beta*log(p[0]/xi0));
		
	//BSS:
	Bsp=B0p*cos(p[1]-beta*log(p[0]/xi0));
	
	//printf("Bsp=%.6e\n",Bsp);
	
	//Calculating the radial and azimutal components:
	
	BC[0]=Bsp*sin(P);
	
	BC[1]=Bsp*cos(P);
	
	BC[2]=0;
	
	//printf("BCX=%.6e, BCY=%.6e, BCZ=%.6e \n",BC[0],BC[1],BC[2]);
	
	//Putting the z component:
	
	BC[0]=BC[0]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[1]=BC[1]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[2]=0;
	
	//printf("BCX=%.6e, BCY=%.6e, BCZ=%.6e \n",BC[0],BC[1],BC[2]);
	
	//Returning to cartesian coordinates:
	
	Math->Cyl2Cart(BG,BC);

	//printf("BGx=%.6e, BGy=%.6e, BGz=%.6e \n",BG[0],BG[1],BG[2]);
	
}

double Physics::Ener2moment(double E, double modp, double c, double m){
	
	//Energy --> moment:
	
	modp=sqrt((E*E)/(c*c)-m*m*c*c);
	
	printf("modp=%.6e\n",modp); 
	
	return modp;
	
}

void Physics::SortMoment(double modp,double m,double p[3]){
	
	double theta1,theta, phi1,phi;
	
		theta1=(rand()%1001);
		theta=theta1/1000;
		
		phi1=(rand()%1001);
		phi=phi1/1000;
		
	//Componentes of the moment in: 
	
	p[0]=modp*sin(theta)*cos(phi);
	
	p[1]=modp*sin(theta)*sin(phi);
	
	p[2]=modp*cos(theta);
	
	printf("px=%.6e, py=%.6e, pz=%.6e \n",p[0],p[1],p[2]);
	
}

double Physics::Ener2vel(double E, double modv, double c, double m){
	
	const double q=1.602*pow(10,-19);
	
	//Energy --> moment:
	
	modv=c*sqrt(1-((m*c*c)/(E))*((m*c*c)/(E)));
	
	printf("beta=%.12e\n",modv/c); 
	
	return modv;
	
}

void Physics::SortVel(double modv,double m,double v0[3]){
	
	double a1, a, b1, b;
	
	a1=(rand()%10001);
	a=a1/10000;
		
	b1=(rand()%10001);
	b=b1/10000;
		
	printf("a=%.6e, b=%.6e \n",a,b); 
		
	//Componentes of the moment in: 
	
	v0[0]=a*modv;
	
	v0[1]=b*modv;
	
	v0[2]=modv*sqrt(1-a*a-b*b);
	
	printf("v0x=%.6e, v0y=%.6e, v0z=%.6e \n",v0[0],v0[1],v0[2]);
	
}

void Physics::kineticEnergy(double K, double modv, double m){
	K=(m*modv)/2;	
}

void Physics::rigidity(double Ri, double modB, double rL){	
	Ri=modB*rL;	
}

double Physics::gammafunc(double vmod, double c){

	double gamma;
	
	gamma=1/sqrt(1-(vmod*vmod)/(c*c));	
	
	return gamma;
	
}





	

	


