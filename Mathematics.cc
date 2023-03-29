//Mathematics.cc

// System Headers:
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Local Headers:
#include "Mathematics.h"

// Constructor
Mathematics::Mathematics ( )       
{
  
}

// Destructor
Mathematics::~Mathematics ( )
{
        
}

//Vector Product(Interessante colocar para retornar o módulo)
double Mathematics::VecProd(double prod[3],double vec1[3], double vec2[3]){
  
  prod[0]=(vec1[1]*vec2[2]-vec1[2]*vec2[1]);
  prod[1]=-(vec1[0]*vec2[2]-vec1[2]*vec2[0]);
  prod[2]=(vec1[0]*vec2[1]-vec1[1]*vec2[0]);
  
  return 0;
  }
  
//Modulus
double Mathematics::Mod(double vec[3])
{
	double modulus=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	
	//printf("vec=(%.3e,%.3e,%.3e) \n", vec[0],vec[1],vec[2]);
	//printf("mod=%.3e \n",modulus);
 	return modulus;
}


//Normalizes a vector
void Mathematics::Norm(double versor[3], double vector[3])
{
	double m;
 	int i;
 	m=Mod(vector);
 	if (m!=0)
	{
  		for(i=0;i<=2;i++)
		{
			versor[i]=vector[i]/m;
		}
	}
}

//Scalar product
double Mathematics::ScalarProd(double vec1[3],double vec2[3])
{
	double scalar,mod1, mod2,theta;
	scalar=(vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2]);	
	return scalar;
}

//Angle between vectors
double Mathematics::Angle2Vec(double vec1[3], double vec2[3]){
	
	double theta, scalar, mod1, mod2;

	//printf("vec1=%.3lf, %.3lf, %.3lf \n",vec1[0],vec1[1],vec1[2]);
	//printf("vec2=%.3lf, %.3lf, %.3lf \n",vec2[0],vec2[1],vec2[2]);

	scalar=ScalarProd(vec1,vec2);
//	printf("scalar=%.9e \n",scalar);
	mod1=Mod(vec1);
	mod2=Mod(vec2);
//printf("mod1=%.9e \n",mod1);
//	printf("mod2=%.9e \n",mod2);
	theta=acos(scalar/(mod1*mod2));
	
	return theta;
	
}
//parallel vector and perpendicular(pe=perpendicular/pa=parallel)
void Mathematics::Projections(double vpar[3],double vper[3],double vec1[3], double vec2[3]){
	//vec1=v0(velocidade), vec2=B(Campo magnético)
	int i,k;
	//double theta, normvec1[3], normvec2[3];
	double v2[3],v3[3];
	
	//printf("BDX=%.6e BDY=%.6e BDZ=%.6e\n",vec2[0],vec2[1],vec2[2]);
		
	//Norm(normvec2,vec2);
	//Norm(normvec1,vec1);
	//theta=Angle2vec(normvec1,normvec2);	
	//theta=Angle2Vec(vec1,vec2);
	//	printf("theta=%.9e \n",theta);
	
	VecProd(v2,vec1,vec2);
	
	//printf("v2X=%.6e v2Y=%.6e v2Z=%.6e\n",v2[0],v2[1],v2[2]);
	
	VecProd(v3,vec2,v2);
	
	//printf("v3X=%.6e v3Y=%.6e v3Z=%.6e\n",v3[0],v3[1],v3[2]);
	
    double vec2mod=Mod(vec2);
    
    //printf("vec2mod=%.6e\n",vec2mod);
    
	for(i=0;i<=2;i++) vper[i]=v3[i]/(vec2mod*vec2mod);	
	//printf("vperX=%.6e vperY=%.6e vpervZ=%.6e\n",vper[0],vper[1],vper[2]);
	
	for(i=0;i<=2;i++) vpar[i]=vec1[i]-vper[i];
	//printf("vparX=%.6e vparY=%.6e vparZ=%.6e\n",vpar[0],vpar[1],vpar[2]);
		
}

void Mathematics::Cart2Esf(double vec1[3], double vec2[3]){
	
	double thetae, phi, re;
	
	re=Mod(vec2);
	
	phi=atan(vec2[1]/vec2[0]);
	
	thetae=atan(sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1])/(vec2[2]));
	
	vec1[0]=re;
	vec1[1]=phi;
	vec1[2]=thetae;
	
	//printf("re=%.9e ,",re);
	//printf("phi=%.9e ",phi);
	//printf("thetae=%.9e \n",thetae);
	
}

void Mathematics::Esf2Cart(double vec1[3], double vec2[3], double esf[3]){
	
	double x, y, z;
	//The esf[3] function is r,phi,theta.
	
	//changing to cartesian:
	
	x=(vec2[2]*cos(esf[2])+vec2[0]*sin(esf[2]))*cos(esf[2]);
	
	y=(vec2[2]*cos(esf[2])+vec2[0]*sin(esf[2]))*sin(esf[2]);
	
	z=vec2[0]*cos(esf[2])-vec2[2]*sin(esf[2]);
	
	//putting the change in the vector:
	
	vec1[0]=x;
	vec1[1]=y;
	vec1[2]=z;
	
}
 
void Mathematics::Cyl2Cart(double vec1[3], double vec2[3]){
	
	//Variable definition
	
	double x,y,z; 
	
	//Changing the coordenate:
	
	x=vec2[0]*cos(vec2[1]);
	
	y=vec2[0]*sin(vec2[1]);
	
	z=vec2[2];
	
	//Puttin in a vector the coordinate change:
	
	vec1[0]=x;
	vec1[1]=y;
	vec1[2]=z;
	
}
  

void Mathematics::Cart2Cyl(double vec1[3], double vec2[3]){
	
	double theta1, rho, z;
	
	rho=sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1]);
	
	theta1=atan(vec2[1]/vec2[0]);
	
	z=vec2[2];
	
	vec1[0]=rho;
	vec1[1]=theta1;
	vec1[2]=z;
	
	//printf("re=%.9e ,",re);
	//printf("phi=%.9e ",phi);
	//printf("thetae=%.9e \n",thetae);
	
}


  
