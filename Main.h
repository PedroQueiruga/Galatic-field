// System Headers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/math/constants/constants.hpp>
#include <chrono>
//#include <Time.h>

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "types.h"

#include "Mathematics.h"
#include "Physics.h"
#include "InputParameters.h"

using namespace boost::multiprecision;

//Defining the precision:

//using Types::float_precision = boost::multiprecision::mpfr_float_100; //To increase precision change 100 to 200 without further changes in the code

//Defining the constants:

	//Physical constants:

		//Elementar charge in coulombs
		const Types::float_precision qe("1.602176634e-19"); 
		
		//Proton rest mass in kg
		const Types::float_precision m_p("1.672621898e-27");
		
		//Eletron rest mass in kg
		const Types::float_precision m_eletron("9.10938356e-31"); 
		
		//Light speed in vacuum
		const Types::float_precision c(299792458.0);
		
		//Permeabilidade magnética do vácuo em T·m/A
		const Types::float_precision mi0 = 4 * boost::math::constants::pi<Types::float_precision>() * Types::float_precision("1e-7");
		
	//Astrophysical constants:

		//Astronomical Units (UA) in meters
		const Types::float_precision UA("1.495978707e11");
		
		//Earth dipole moment in A·m²
		const Types::float_precision  mi("8.00e22");
		
		//Radius of Sun's orbit around the galatic center in meters
		const Types::float_precision rs("2.469e20");
		
	//Conversion factors
	
		//Conversion meters to kiloparsec	
		const Types::float_precision kp("3.2407792700054e-20");
	
	
		//Conversion meters to megaparsec
		const Types::float_precision mpc("3.240779289e-23");
	
		
//Now, lets define other important variables of the program:


//Time between each step:

Types::float_precision passo("1e7"); //If you drecrease the step, the number of points increase. If you increase the step, the number of points descrease
Types::float_precision t_passo;
int i,j,k,l,counter=0;

//Initial conditions to be defined at the beginning of the simulation:

//int specie=1, model=1, turbulence=0;
//int mapping=0;
//Types::float_precision r0[3]={-8.5,0,0};
//Types::float_precision energy=1*pow(10, 18); 

int specie,model,turbulence,mapping;
Types::float_precision r0[3],energy; // Energy in eV.
Types::float_precision rx0,ry0,rz0; //In kpc - The actual distance is equivalente a the distance to the earth from the galatic center

//Special: mapping (0:True, 1:False)
//1  Species:(1 proton;2 helium;3 carbono;4 nitrogen;5 oxygen;6 aluminum;7 silicon;8 iron;9 eletron);
//2  Model:(0 ASS; 1 BSS);
//3  r0: Defines the initial position 
//4  energy: Initial energy of the particle --> Use to get the velocity
//5 turbulence:(0 turbulence is on, if 1 turbulence is off)
//6 Mapping:(0 no mapping; 1 xy mapping; 2 circular mapping)

//Defining constants to the galaxy and particles:

Types::float_precision q_v[10]={0,1,2,6,7,8,13,14,26,-1},q; //Define the charges
Types::float_precision m_0,mr,m_v[10]={0,1,4,12,14,16,27,28,56, 0.0005446623093681918}; //Define the masses
Types::float_precision espessura_galac=3.086*pow(10,18), raio_galac=20;
int galac_sphere_raio=20,inferior_limit_galaxy=1;

//espessura_galac:Espessura da galaxia ~ 100 pc ~ 0.1 kpc, raio_galac:Raio da galaxia ~ raio_galac=2.314*pow(10,20)15 kpc 
//galac_sphere_raio: Define the limite for the halo, in kpc.
//Inferior_limit_galaxy:Define the inferior limit for the magnétic field, in kpc

//Defining other important variables for the system:

Types::float_precision t,w,T,m;
Types::float_precision modr,modv,modB,modF,modp,modp0,modvper,modvpar,angle;
Types::float_precision r[3],v[3],v0[3],a[3];
Types::float_precision F[3],B[3],B0[3],BG[3],p[3],p0[3],vpar[3],vper[3],prod[3],vpera[3];
Types::float_precision x_min,y_min,z_min,x_max,y_max,z_max;
Types::float_precision t_escape,v_inicial,r_inicial,count2=0,V_inicial[3];
Types::float_precision modrkpc; //Descreve o módulo do raio nas unidades de kpc.
Types::float_precision phi0,modularv;
Types::float_precision K,Ri,rL,rL0,vol;
Types::float_precision theta,initialy,gammaL;
Types::float_precision randomic;
Types::float_precision rotB[3], BGT[3];
Types::float_precision theta1,phi1,rand1,rand2; //This are used to randomize the velocity direction.

//Variable to calculate the mean values

Types::float_precision meanB[3],modmeanB;

//Variables to correct the galatic magnetic flied velocity:

Types::float_precision vc,modv0,correction=1*pow(10,-16);
Types::float_precision betavelocity,vnorm[3];
Types::float_precision gammatest;

//Variaveis para mapear o campo magnético galáctico

int contador=1,thetaG=0;
Types::float_precision radiusG=1, thetaradG,radiusGm; // Radius in kpc, theta in Degrees
Types::float_precision posx=-20,posy=-20; //Position in kpc

//Variáveis para fazer o plot do movimento dentro do plano (plane.dat)

Types::float_precision vertical, horizontal; //Definindo as variaveis para controle de escape.
Types::float_precision vertical_limit=0.05, horizontal_limit=10; //Ambas com a distância em kpc
Types::float_precision vertical_kpc, horizontal_kpc;
Types::float_precision escape_time;

//Correção da Velocidade da luz:
Types::float_precision factor;

//Desvio da tragetória da partícula:

Types::float_precision desvio_rad, desvio_grau,cos_theta,desvio_grau0=0;

//Calculo do tempo de escape:

Types::float_precision counter_escape = 0;

//Limitando o tempo de cada passo:

Types::float_precision dt_min = 1.0e7, dt_max = 1.0e7, time_factor=0.001,travel_time=0; //Increase the time factor make each step more precise
Types::float_precision modq; //Cálcula o módulo da carga para evitar problemas

//Deflection constants:

Types::float_precision deflection[3]; 

#endif // MAIN_H_INCLUDED
