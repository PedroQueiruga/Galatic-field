// System Headers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstdlib>

#include "Mathematics.h"
#include "Physics.h"
#include "InputParameters.h "
//#include "Atmosphere.h"

//Global variables

//char ch;
//char string[8],line[100];
//double altitude[1481],temperature[1481],pressure[1481],density[1481];

const double qe=1.602*pow(10,-19); //carga de um próton 1.602E(-19)
double m=1.672*pow(10.0, -27); //massa de um próton
double m_eletron= 9.109*pow(10, -31); //massa de um elétron
const double UA=1.495978707*pow(10,11); //unidades astronômicas
const double c=299792458; //Light velocity
const double mi0=12.5663706143592*pow(10,-7);
const double mi=8.00*pow(10,22);
const double rs=2.469*pow(10,20); //radius of sun's orbit
const double kp=3.24078*pow(10,-20); //meters to kiloparsec


double passo=1*pow(10,6);
double p0[3],modp0;

//Antigamente o tempo deveria ser na ordem de 10 a 6, quando consideramos a fracao do período

int i,j,k,l,counter=0, interaction=10, fraction=10000, relativistic=0, specie=8, model=3;
double t,w,T;
double modr,modv,modB,modF,modp;
double q_v[10]={0,1,2,6,7,8,13,14,26,-1},q;
double espessura_galac=3.086*pow(10,18), raio_galac=15; //espessura_galac:Espessura da galaxia ~ 100 pc ~ 0.1 kpc, raio_galac:Raio da galaxia ~ raio_galac=2.314*pow(10,20)15 kpc
double vertical, horizontal; //Definindo as variaveis para controle de escape.
double t_escape,v_inicial,r_inicial,count2=0;
double t_passo;
double galac_sphere_raio=10;
double phi0,modularv;

double O[3]={0,0,0};
double F[3],B[3],B0[3],BD[3],BG[3],p[3];
double r[3],v[3],v0[3],a[3],angle,modvper,modvpar;
double m_0,mr,m_v[10]={0,1,4,12,14,16,27,28,56, 0.0005446623093681918};
//float energy=1*pow(10, 10);
float v0x,v0y,v0z,rx0,ry0,rz0;
double gamma;
double theta,initialy;
//double r0[3]={1.5,1.5,0};
double r0[3]={5.9,5.8,0}; //In kpc - The actual distance is equivalente a the distance from earth
double energy=1*pow(10, 16); // Energy in eV.

/*
0.25=1.77828
0.5=3.16228
0.75=5.62341

*/

double vpar[3],vper[3];
double x_min,y_min,z_min,x_max,y_max,z_max;
double prod[3],rL,rL0;
double vol;
double K,Ri;

//1  particle Species(1 proton;2 helium;3 carbono;4 nitrogen;5 oxygen;6 aluminum;7 silicon;8 iron;9 eletron)
//2  magnetic field model:(0 Uniform;1 Variable;2 Dipolar; 3 Galactic),
//3  Number of interactions, fraction of the time
//4  0:Non relativistic, 1:Relativistic
//5  Initial energy(Em eV) - limite era 1E16
//6  Initial velocity(Em relacao a luz)
//7  Initial position (In dipole the module of the initial position must be !=0)















