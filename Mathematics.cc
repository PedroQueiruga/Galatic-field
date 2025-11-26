//Mathematics.cc

// System Headers:
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <random>
#include <fstream>

// Local Headers:
#include "Mathematics.h"
#include "types.h"

using namespace boost::multiprecision;

// Constructor
Mathematics::Mathematics ( ) : dist (0.0, 1.0)       
{

	std::random_device rd;
	
	engine.seed(rd());
  
}

// Destructor
Mathematics::~Mathematics ( )
{
        
}

//Vector Product
void Mathematics::VecProd(Types::float_precision prod[3],const Types::float_precision vec1[3], const Types::float_precision vec2[3]){
  
  prod[0]=(vec1[1]*vec2[2]-vec1[2]*vec2[1]);
  prod[1]=-(vec1[0]*vec2[2]-vec1[2]*vec2[0]);
  prod[2]=(vec1[0]*vec2[1]-vec1[1]*vec2[0]);
 
  }
  
//Modulus

Types::float_precision Mathematics::Mod(const Types::float_precision vec[3])
{
	Types::float_precision modulus=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	
 	return modulus;
}


//Normalizes a vector
void Mathematics::Norm(Types::float_precision versor[3], const Types::float_precision vector[3])
{
	Types::float_precision m;
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
Types::float_precision Mathematics::ScalarProd(const Types::float_precision vec1[3],const Types::float_precision vec2[3])
{
	Types::float_precision scalar,mod1, mod2,theta;
	scalar=(vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2]);	
	return scalar;
}

//Angle between vectors

Types::float_precision Mathematics::Angle2Vec(const Types::float_precision vec1[3], const Types::float_precision vec2[3]){
	
	Types::float_precision theta, scalar, mod1, mod2;

	scalar=ScalarProd(vec1,vec2);

	mod1=Mod(vec1);
	mod2=Mod(vec2);

	theta=acos(scalar/(mod1*mod2));
	
	return theta;
	
}

//parallel vector and perpendicular(pe=perpendicular/pa=parallel)

void Mathematics::Projections(Types::float_precision vpar[3],Types::float_precision vper[3],const Types::float_precision vec1[3], const Types::float_precision vec2[3]){
	//vec1=v0(velocidade), vec2=B(Campo magnético)
	int i;
	//Types::float_precision theta, normvec1[3], normvec2[3];
	Types::float_precision v2[3],v3[3],v4[3];
	
	VecProd(v2,vec1,vec2);
	
	VecProd(v3,vec2,v2);
	
    	Types::float_precision vec2mod=Mod(vec2);
    
	for(i=0;i<=2;i++) vper[i]=v3[i]/(vec2mod*vec2mod);	
	//printf("vperX=%.6e vperY=%.6e vpervZ=%.6e\n",vper[0],vper[1],vper[2]);
	
	for(i=0;i<=2;i++) vpar[i]=vec1[i]-vper[i];
	
}

void Mathematics::Cart2Esf(Types::float_precision vec1[3], const Types::float_precision vec2[3]){
	
	Types::float_precision thetae, phi, re;
	
	re=Mod(vec2);
	
	phi=atan2(vec2[1],vec2[0]);
	
	thetae=atan(sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1])/(vec2[2]));
	
	vec1[0]=re;
	vec1[1]=phi;
	vec1[2]=thetae;
	
	
}

void Mathematics::Esf2Cart(Types::float_precision vec1[3], const Types::float_precision vec2[3], const Types::float_precision esf[3]){
	
	Types::float_precision x, y, z;
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
 
void Mathematics::Cyl2Cart(Types::float_precision vec1[3], const Types::float_precision vec2[3]){
	
	//Variable definition (vec2[0-Brho,1-Bphi,2-Bz])
	
	Types::float_precision x,y,z; 
	
	//Changing the coordinates:
	
	x=vec2[0]*cos(vec2[1])-vec2[1]*sin(vec2[1]);
	
	y=vec2[0]*sin(vec2[1])+vec2[1]*cos(vec2[1]);
	
	z=vec2[2];
	
	//Puttin in a vector the coordinate change:
	
	vec1[0]=x;
	vec1[1]=y;
	vec1[2]=z;
	
	//printf("X=%.3e , Y=%.3e , Z=%.3e",vec1[0],vec1[1],vec1[2]);
	
}

void Mathematics::Cart2Cyl(Types::float_precision vec1[3], const Types::float_precision vec2[3]){
	
	Types::float_precision theta1, rho, z;
	
	//printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",vec2[0],vec2[1],vec2[2]);
	
	rho=sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1]);
	
	theta1=atan(vec2[1]/vec2[0]);
	
	z=vec2[2];
	
	//printf("Theta(antes)=%.6e graus ",theta1*57.2958);
	
	//Fazendo o módulo para o ângulo se tornar positivo:
	/*
	if(theta1>=0){	
		theta1=theta1;		
	}		
	if(theta1<=0){	
		theta1=-theta1;
	}
	
	//Ajustando os quadrantes:
	
	if(vec2[0]<0  vec2[1]>0){
		
		theta1=theta1+1.5708;	
	}
	if(vec2[0]<0  vec2[1]<0){
		
		theta1=theta1+3.14159;		
	}
	if(vec2[0]>0  vec2[1]<0){
		
		theta1=theta1+4.71239;	
	}
	*/
	
	//Testando Ajuste:
	
	theta1 = atan2(vec2[1], vec2[0]);

	if (theta1 < 0) {
    	theta1 += 2 * 3.14159; // Ajusta o ângulo para o intervalo de 0 a 2p radianos (0 a 360 graus)
	}
	
	//printf("Theta=%.6e graus \n",theta1*57.2958);
	
	//Os angulos estão em radianos, e necessario realizar a conversao
	
	
	vec1[0]=rho;
	vec1[1]=theta1;
	vec1[2]=z;
	
	//printf("re=%.9e ,",re);
	//printf("phi=%.9e ",phi);
	//printf("thetae=%.9e \n",thetae);
	
}

Types::float_precision Mathematics::random(){
    
    //Types::float_precision rd=(rand()%1001);
	//randomic=rd/1000;
	
	double random_double = dist(engine);
	
	return static_cast<Types::float_precision>(random_double);
	
	//randomic = (Types::float_precision&&)rand()/RAND_MAX;
 
    //printf("randomic = %.6e \n", randomic);
    
    //return randomic;
    
}

void Mathematics::rotationX(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta){
	
   //Defining the matrices where the first term is the line, the second is the collunm. 
   	
    Types::float_precision Rx[3][3] = { {1, 0, 0}, {0, cos(theta), -sin(theta)}, {0,sin(theta),cos(theta)}}; //each {{line 1 terms},{line 2 terms},{line 3 terms}}
    //int b[3][1] = {{1},{1},{2}}; --> BG[0]=b[0][0], BG[1]=b[1][0], BG[2]=b[2][0]
    //int c[3][1]; --> rotB
   
    rotB[0]=Rx[0][0]*BG[0]+Rx[0][1]*BG[1]+Rx[0][2]*BG[2]; //OK
    rotB[1]=Rx[1][0]*BG[0]+Rx[1][1]*BG[1]+Rx[1][2]*BG[2]; //OK
    rotB[2]=Rx[2][0]*BG[0]+Rx[2][1]*BG[1]+Rx[2][2]*BG[2]; //OK
    
    //printf("rotBx=%.6e, rotBy=%.6e, rotBz=%.6e",rotB[0],rotB[1],rotB[2]);
	
}

void Mathematics::rotationY(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta){
	
   //Defining the matrices where the first term is the line, the second is the collunm. 
   
    Types::float_precision Ry[3][3] = { {cos(theta), 0, sin(theta)}, {0, 1, 0}, {-sin(theta),0,cos(theta)}}; 
    //int b[3][1] = {{1},{1},{2}}; --> BG[0]=b[0][0], BG[1]=b[1][0], BG[2]=b[2][0]
    //int c[3][1]; --> rotB
    
    //printf("theta=%.4e AQUI \n ",theta);
    
    //Fazendo a multiplicação de matrizes
    
    rotB[0]=Ry[0][0]*BG[0]+Ry[0][1]*BG[1]+Ry[0][2]*BG[2];
    rotB[1]=Ry[1][0]*BG[0]+Ry[1][1]*BG[1]+Ry[1][2]*BG[2];
    rotB[2]=Ry[2][0]*BG[0]+Ry[2][1]*BG[1]+Ry[2][2]*BG[2];
    
    //printf("rotBx=%.6e, rotBy=%.6e, rotBz=%.6e",rotB[0],rotB[1],rotB[2]);
	
}

void Mathematics::rotationZ(Types::float_precision rotB[3], const Types::float_precision BG[3], const Types::float_precision& theta){
	
   //Defining the matrices where the first term is the line, the second is the collunm. 
   
    Types::float_precision Rz[3][3] = { {cos(theta),-sin(theta), 0}, {sin(theta),cos(theta), 0}, {0,0,1}}; 
    //int b[3][1] = {{1},{1},{2}}; --> BG[0]=b[0][0], BG[1]=b[1][0], BG[2]=b[2][0]
    //int c[3][1]; --> rotB
    
    //Fazendo a multiplicação de matrizes
    
    rotB[0]=Rz[0][0]*BG[0]+Rz[0][1]*BG[1]+Rz[0][2]*BG[2];
    rotB[1]=Rz[1][0]*BG[0]+Rz[1][1]*BG[1]+Rz[1][2]*BG[2];
    rotB[2]=Rz[2][0]*BG[0]+Rz[2][1]*BG[1]+Rz[2][2]*BG[2];
    
    //printf("rotBx=%.6e, rotBy=%.6e, rotBz=%.6e",rotB[0],rotB[1],rotB[2]);
	
}

Types::float_precision Mathematics::angleX(const Types::float_precision vec1[3]){
	
	Types::float_precision angle,modvec1;
	
	modvec1=Mod(vec1);
	
	//printf("modvec1=%.6e \n",modvec1);
	
	angle=acos(vec1[0]/modvec1); //radianos
	
	return angle;
}

Types::float_precision Mathematics::angleY(const Types::float_precision vec1[3]){
	
	Types::float_precision angle,modvec1;
	
	modvec1=Mod(vec1);
	
	//printf("modvec1=%.6e \n",modvec1);
	//printf("vec1[1]=%.6e \n",vec1[1]);
	
	angle=acos(vec1[1]/modvec1); //radianos
	
	return angle;
}

Types::float_precision Mathematics::angleZ(const Types::float_precision vec1[3]){
	
	Types::float_precision angle,modvec1;
	
	modvec1=Mod(vec1);
	
	//printf("modvec1=%.6e \n",modvec1);
	//printf("vec1[2]=%.6e \n",vec1[2]);
	
	angle=acos(vec1[2]/modvec1); //radianos
	
	return angle;
}

  
