//Physics.cc

// System Headers:
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

// Local Headers:
#include "Physics.h"
#include "Mathematics.h"
#include "types.h"

using namespace boost::multiprecision;

// Constructor
Physics::Physics ( )       
{
  
}

// Destructor
Physics::~Physics ( )
{
        
}

//Lorentz force
void Physics::FLorentz(Types::float_precision F[3], const Types::float_precision& q, const Types::float_precision v[3], const Types::float_precision B[3])
{
	
	Mathematics Math;
	Types::float_precision prod[3];
	Math.VecProd(prod,v,B);
	
	for(int i=0;i<=2;i++) F[i]=q*prod[i];
	
}

//Velocity
void Physics::Velocity(Types::float_precision v[3],const Types::float_precision v0[3],const Types::float_precision a[3],const Types::float_precision& t)
{
  Mathematics Math;
  int i,k;
  Types::float_precision v2[3];
  
  for(i=0;i<=2;i++) {
	  v[i]=v0[i]+(a[i]*t);
  } 

  Types::float_precision vv=Math.Mod(v); 
   
  Math.Norm(v2,v); 
  
  Types::float_precision v0n=Math.Mod(v0); 
		
  for(k=0;k<=2;k++) v[k]=v2[k]*v0n;
  
}

//Particle trajectory
void Physics::Trajectory(Types::float_precision r[3],const Types::float_precision r0[3],const Types::float_precision v0[3],const Types::float_precision a[3],const Types::float_precision& t)
{
		
  for(int i=0;i<=2;i++) r[i]=r0[i]+v0[i]*t+0.5*(a[i]*t*t);
  
}

//Angular velocity

void Physics::Angvelocity(Types::float_precision& w,const Types::float_precision& q,const Types::float_precision& B,const Types::float_precision& m)
{
	w=(q*B)/m;
}

//Moviment period

void Physics::period(Types::float_precision& T,const Types::float_precision& w)
{	
	
	T=(2*constants::pi)/w;
	
}

//Larmor Radius

void Physics::Larmor(Types::float_precision& rL,const Types::float_precision& m,const Types::float_precision& q,const Types::float_precision& vmod,const Types::float_precision& bmod)
{
		
	rL=(m*vmod)/(q*bmod);
	
}

//Pitch angle

void Physics::Pitch(const Types::float_precision vper[3],const Types::float_precision vpar[3]){
	
	Mathematics Math;
	Types::float_precision vmodper,vmodpar, angle;
	
	vmodpar=Math.Mod(vpar);
	vmodper=Math.Mod(vper);
	
	angle=atan(vmodper/vmodpar);

}

//Relativistic Mass

	
void Physics::Relat(Types::float_precision& m,const Types::float_precision& m_0,const Types::float_precision v[3]){

	Mathematics Math;
	
	
	Types::float_precision gammaL,vtmod;
	const Types::float_precision c("299792458.0");
	
	vtmod=Math.Mod(v);
	
	gammaL=gammafunc(vtmod,c);
	
//	gama=1/sqrt(1-(vtmod*vtmod)/(c*c));
	
//	printf("gama=%.4e \n",gama);
	//printf("m_0=%.4e \n",m_0);
	
	m=m_0*gammaL;
	
		
}

//Galatic Model ASS

void Physics::GalacticASS(Types::float_precision BG[3],const Types::float_precision r[3]){
	
	Mathematics Math;
	Types::float_precision p[3], BC[3];
	Types::float_precision Bsp, B0p;
	
	//constants definition:
	
	Types::float_precision xi0=3.25539*pow(10.0,20), r0=2.623*pow(10.0,20),rho1=6.171*pow(10.0,19);
	Types::float_precision z1=9.257*pow(10.0,18),z2=1.234*pow(10.0,20);
	Types::float_precision betaconst=-5.67, P=-0.174572; 
	
	//P is in radians;
	
	//Convert from cartesian to polar coordinates: 
	//r[0]=x,r[1]=y,r[2]=z --> p[0]=rho,p[1]=theta,p[2]=z
	
	//printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r[0],r[1],r[2]);
	
	Math.Cart2Cyl(p,r);
	
	//printf("Theta=%.6e graus \n",p[1]*57.2958);
	
	//printf("x=%.6e, y=%.6e, theta=%.6e rad=%.6e graus, z=%.6e \n",r[0],r[1],p[1],p[1]*57.2958,p[2]);
	
	//Calculating the ASS (in Tesla)
	
	B0p=((3*r0)/p[0])*tanh(p[0]/rho1)*tanh(p[0]/rho1)*tanh(p[0]/rho1)*pow(10.0,-10); 
	
	
	Bsp=B0p*cos(p[1]-betaconst*log(p[0]/xi0))*cos(p[1]-betaconst*log(p[0]/xi0));
	
	//printf("Bsp=%.6e\n",Bsp);
	
	//Calculating the radial and azimutal components:
	
	BC[0]=Bsp*sin(P);
	
	BC[1]=Bsp*cos(P);
	
	BC[2]=0;
	
	//printf("BCX=%.6e, BCY=%.6e, BCZ=%.6e \n",BC[0],BC[1],BC[2]);
	
	//Putting the z component (This is the symmetric S model):
	
	BC[0]=BC[0]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[1]=BC[1]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[2]=0;
	
	//Returning to cartesian coordinates:
	
	BG[0]=BC[0]*cos(p[1])-BC[1]*sin(p[1]);
	
	BG[1]=BC[0]*sin(p[1])+BC[1]*cos(p[1]);
	
	BG[2]=BC[2];
	
	
}

//Galatic Model BSS

void Physics::GalacticBSS(Types::float_precision BG[3],const Types::float_precision r[3]){
	
	Mathematics Math;
	Types::float_precision p[3], BC[3];
	Types::float_precision Bsp, B0p;
	
	//constants definition:
	
	Types::float_precision xi0=3.25539*pow(10.0,20), r0=2.623*pow(10.0,20),rho1=6.171*pow(10.0,19);
	Types::float_precision z1=9.257*pow(10.0,18),z2=1.234*pow(10.0,20);
	Types::float_precision betaconst=-5.67, P=-0.174572; 
	
	//P is in radians;
	
	//Convert from cartesian to polar coordinates: 
	//r[0]=x,r[1]=y,r[2]=z --> p[0]=rho,p[1]=theta,p[2]=z
	
	//printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r[0],r[1],r[2]);
	
	Math.Cart2Cyl(p,r);
	
	//printf("Theta=%.6e graus \n",p[1]*57.2958);
	
	//printf("x=%.6e, y=%.6e, theta=%.6e rad=%.6e graus, z=%.6e \n",r[0],r[1],p[1],p[1]*57.2958,p[2]);
	
	//Calculating the BSS (In Tesla):
	
	B0p=((3*r0)/p[0])*tanh(p[0]/rho1)*tanh(p[0]/rho1)*tanh(p[0]/rho1)*pow(10.0,-10);
	
	Bsp=B0p*cos(p[1]-betaconst*log(p[0]/xi0));
	
	//printf("Bsp=%.6e\n",Bsp);
	
	//Calculating the radial and azimutal components:
	
	BC[0]=Bsp*sin(P);
	
	BC[1]=Bsp*cos(P);
	
	BC[2]=0;
	
	//printf("BCX=%.6e, BCY=%.6e, BCZ=%.6e \n",BC[0],BC[1],BC[2]);
	
	//Putting the z component (This is the symmetric S model):
	
	BC[0]=BC[0]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[1]=BC[1]*(1/(2*cosh(p[2]/z1))+1/(2*cosh(p[2]/z2)));
	
	BC[2]=0;
	
	//printf("BCX=%.6e, BCY=%.6e, BCZ=%.6e \n",BC[0],BC[1],BC[2]);
	
	//Returning to cartesian coordinates:
	
	
	BG[0]=BC[0]*cos(p[1])-BC[1]*sin(p[1]);
	
	BG[1]=BC[0]*sin(p[1])+BC[1]*cos(p[1]);
	
	BG[2]=BC[2];
	
}

//Conversion energy to velocity in relativistic conditions

void Physics::Ener2vel(const Types::float_precision& E, Types::float_precision& modv, const Types::float_precision& c, const Types::float_precision& m){
	
	const Types::float_precision q("1.602176634e-19"); 
	
	std::cout << std::scientific << std::setprecision(6);
	std::cout << "E =" << E << ",modv =" << modv << ",c = " << c << ", m_0 = " << m << "\n";
	//std::cout << std::scientific << std::setprecision(20) << "modv=" << modv << "\n";
	//m is the rest mass
	
	//Energy --> moment:
	
	modv=c*sqrt(1-(((m*c*c)/(E))*((m*c*c)/(E))));
	
}

//Gamma lorentz function

Types::float_precision Physics::gammafunc(const Types::float_precision& vmod,const Types::float_precision& c){

	Types::float_precision gammaL;
	
	gammaL=1/sqrt(1-(vmod*vmod)/(c*c));	
	
	return gammaL;
	
}

//TUrbulence funciton

void Physics::turbulence(Types::float_precision BGT[3], const Types::float_precision BG[3]){
	
	Mathematics Math;
	
	int k;
	Types::float_precision rotB[3], rotB2[3],rho,modBG; //rotB e a primeira rotacao, rotB2 representa a segunda rotacao
	Types::float_precision turbulence,phiturb; //BGT[3] seria a versao turbulenta no outro sistema de coordenadas
	Types::float_precision normBGT[3]; //This will be the norm of BGT
	Types::float_precision theta, phi, thetaturb=0.10072295;
	Types::float_precision Bper[3],Bpar[3],rotBNper[3];	
	//printf("Phi=%.16e rad = %.4e graus, theta=%.4e rad = %.4e graus \n",phi,phi*rad2deg,theta,theta*rad2deg);
	
	//std::cout << std::scientific << std::setprecision(18) << "Bx = " << BG[0] << ",By = " << BG[1] << ",Bz = " << BG[2] << ",thetaturb = " << thetaturb << "\n";
	//1:Rotating the original magnetic field around Z axis:
	
		theta=Math.angleX(BG);
		Math.rotationZ(rotB,BG,-theta); 
		
		//printf("theta=%.16e rad = %.4e graus \n",theta,theta*rad2deg);
		
		//printf("rotBx=%.6e, rotBy=%.6e, rotBz=%.6e \n",rotB[0],rotB[1],rotB[2]);
		
		
	//2:Rotating the magnetic field in X axis around Y:
	
		phi=Math.angleZ(rotB);
		Math.rotationY(rotB2,rotB,-phi);
		
		//printf("phi=%.16e rad = %.4e graus \n",phi,phi*rad2deg);
		
		//printf("rotB2x=%.6e, rotB2y=%.6e, rotB2z=%.6e \n",rotB2[0],rotB2[1],rotB2[2]);
		
		
	//3:Calculating the spherical componente:
	
		//3.1:Calculating the turbulence in the angle phi:
			
			turbulence=Math.random();
	
			phiturb=turbulence*2*constants::pi;
			
		//3.2:Calculating the modulos of the rotate magnetic field:
		
			modBG=Math.Mod(rotB2);
			//printf("modB2=%.4e \n",modB2);
			
		//3.3:Calculating the components of the new magnetic field:
			
			BGT[0] = modBG*cos(phiturb)*sin(thetaturb);
	
			BGT[1] = modBG*sin(phiturb)*sin(thetaturb);
	
			BGT[2] = modBG*cos(thetaturb);
		
			//printf("BGTx=%.6e, BGTy=%.6e, BGTz=%.6e \n",BGT[0],BGT[1],BGT[2]);
			//printf("AngleB0BGT=%.6e\n",angleB0BGT*rad2deg);
			//printf("phiturb=%.16e rad = %.4e graus \n",phiturb,phiturb*rad2deg);
			
			//exit(0);
	//4:Rotating the magnetic field around Y:
	
		Math.rotationY(rotB,BGT,phi);
			
	//5:Rotating the magnetic field around Z:
	
		Math.rotationZ(rotB2,rotB,theta);
		
	//6:Ensuring that the rotated field has the correct direction and modules:
	
		Math.Norm(normBGT,rotB2); 
  		Types::float_precision modnormBGT=Math.Mod(rotB2); 	
  		for(k=0;k<=2;k++) BGT[k]=normBGT[k]*modnormBGT;
  		
	//7: Printing the final results and comparisons:
	
		Types::float_precision BGTmod=Math.Mod(BGT);
		Types::float_precision angleB0BGT=Math.Angle2Vec(BG,BGT);
		//modBG=Math.Mod(BG);
		//std::cout << std::scientific << std::setprecision(18) << "modBG=" << modBG << "BGTmod = " << BGTmod << "\n";
		//printf("BGx=%.6e, BGy=%.6e, BGz=%.6e, |BG|=%.10e \n",BG[0],BG[1],BG[2],modBG);
		//printf("BGTx=%.6e, BGTy=%.6e, BGTz=%.6e, |BGT|=%.10e \n",BGT[0],BGT[1],BGT[2],BGTmod);
		//printf("AngleB0BGT=%.6e\n",angleB0BGT*rad2deg);
		
		//Types::float_precision diferenca_percentual = (abs(BGTmod - modBG) / modBG) * 100;
        	//std::cout << std::scientific << std::setprecision(18)  << "  - Variação devida à turbulência: " << diferenca_percentual << " %" << std::endl;
	
}

//Functions to map the magnetic field under two different conditions:

void Physics::mappingxy(Types::float_precision& posx,Types::float_precision& posy,int model){
		
		Mathematics Math;
		
		std::ofstream outfile3("mapping.dat");
		std::ofstream outfile5("magneticvector.dat");
		
		int contador=1;
		const Types::float_precision kp("3.2407792700054e-20");
		Types::float_precision r0[3], BG[3], modB;

		while(posy<=20){
			while(posx<=20){
					
				//Calculando a posicao da particula:
					r0[0]=posx/kp;
					r0[1]=posy/kp;
					r0[2]=0;
				
				//Calculando o campo magnetico na posicao da particula:
				
					if(model==0){
						GalacticASS(BG,r0); 
					}
					if(model==1){
						GalacticBSS(BG,r0); 
					} 
					if(posy==0 and posx==0){
						BG[0]=0;
						BG[1]=0;
						BG[2]=0;
					}
					
					std::cout << "Countador=" << contador << std::scientific << std::setprecision(6) << ", BGx=" << BG[0] << ", BGy=" << BG[1] << ", BGz=" << BG[2] << "\n";
					
					modB = Math.Mod(BG);
					 
					outfile3 << std::scientific << std::setprecision(6) << r0[0] * kp << " " << r0[1] * kp << " " << modB << "\n"; //onde a posiacao esta em kpc

					outfile5 << std::scientific << std::setprecision(6) << r0[0] * kp << " " << r0[1] * kp << " " << BG[0] << " " << BG[1] << "\n";
					
					//fprintf(outfile7,"%.3e %.3e %.3e \n",radiusG,thetaG,modB);
					
				//Aumentando o x:
				    posx=posx+1;
				    contador=contador+1;
			}
			posy=posy+1;
			posx=-20;
		}
		
}

void Physics::mappingcircular(Types::float_precision& radiusG,int thetaG, int model){
	
	Mathematics Math;
	
	std::ofstream outfile3("mapping.dat");
	std::ofstream outfile5("magneticvector.dat");
			
	int contador=1;
	const Types::float_precision kp("3.2407792700054e-20");
	Types::float_precision thetaradG,radiusGm;
	Types::float_precision r0[3], BG[3], modB;;
		
	while(radiusG<=20){
			while(thetaG<=360){
				
				//Convertendo os respectivos valores para as unidades do sistema
					radiusGm=radiusG/kp; //kpc --> m
					thetaradG=(thetaG*constants::pi)/180; // Graus --> Radianos
					//printf("radiusGm=%.5e \n",radiusGm);
					//printf("thetaG=%.6e graus = %.6e rad \n",thetaG,thetaradG);
					
				//Calculando a posicao da particula:
					r0[0]=radiusGm*cos(thetaradG);
					r0[1]=radiusGm*sin(thetaradG);
					r0[2]=0;
				
				    //printf("x=%.10e , y=%.10e , z=%.6e, Theta=%.3e \n",r0[0]*kp,r0[1]*kp,r0[2],thetaG);
				    //printf("x=%.6e, y=%.6e, Theta=%d ",r0[0],r0[1],thetaG);
				//Calculando o campo magnetico na posicao da particula:
					if(model==0){
						GalacticASS(BG,r0); 
					}
					if(model==1){
						GalacticBSS(BG,r0); 
					}
					
					std::cout << "Countador=" << contador << std::scientific << std::setprecision(6) << ", BGx=" << BG[0] << ", BGy=" << BG[1] << ", BGz=" << BG[2] << "\n";
					
					modB = Math.Mod(BG);
					 
					outfile3 << std::scientific << std::setprecision(6) << r0[0] * kp << " " << r0[1] * kp << " " << modB << "\n"; //onde a posiacao esta em kpc
					
					if(radiusG<=10){
						outfile5 << std::scientific << std::setprecision(6) << r0[0] * kp << " " << r0[1] * kp << " " << BG[0] << " " << BG[1] << "\n";
					}
					
				//Aumentando o Angulo:
				    thetaG=thetaG+1;
				    contador=contador+1;
			}
			 
			radiusG=radiusG+0.1;
			thetaG=0;
		}
		
	
}

//Relativistic Acceleration

void Physics::accelerationRelativity(Types::float_precision a[3], const Types::float_precision F[3], const Types::float_precision v[3], const Types::float_precision& m_0){
	
	Mathematics Math;
	
	int k;
	Types::float_precision gammaL,vmodular, scalarFv;
	Types::float_precision atest[3];
	const Types::float_precision c("299792458.0");
	
	//printf("Fx=%.6e Fy%.6e Fz=%.6e // vx=%.6e vy%.6e vz=%.6e //  \n",F[0],F[1],F[2],v[0],v[1],v[2]);
	
	vmodular=Math.Mod(v);
	
	gammaL=gammafunc(vmodular,c);
	
	scalarFv=Math.ScalarProd(F,v);
	
	for(k=0;k<=2;k++) {
				a[k]=(1/(gammaL*m_0))*(F[k]-((scalarFv*v[k])/(c*c)));
			}
			
	//printf("ax=%.6e ay=%.6e az=%.6e \n",a[0],a[1],a[2]);

}

