#include <cstdlib>
#include <iostream>

using namespace std;

//InputParameters.cc/

//local headers/
#include "InputParameters.h"

FILE  *parameters_in;

//constructor of the class/
InputParameters::InputParameters ( ){

}

//destructor of the class/
InputParameters::~InputParameters ( ){

}


//methods of the Input Parameters class
void InputParameters::ReadingInputParameters(int specie,int model,int interaction,int fraction,int relativistic,float energy,float v0x,float v0y,float v0z,float rx0,float ry0,float rz0){//1 
 	
 	int i;
 	char line[1000];
 	
 	int ncols,nlines = 0;
 	
 	FILE * inputfile;

	//(void)printf("Entre com o nome do arquivo\n");
	//scanf("%s",&ArqName);
	//inputfile=fopen(ArqName,"r");
	inputfile=fopen("inputparameters2.dat","r");


	if (inputfile==NULL) {
	printf("Can`t open inputfile\n");
	system("PAUSE");
	}

/*while(1){ 
int ch;
ch=fgetc(inputfile);

if (ch==EOF) break; //colocar um contador de linhas no meu
//printf ("%c\n",ch);

(void)ungetc(ch,inputfile);

*/

fgets(line,sizeof(line),inputfile);
printf("%s", line);
nlines ++;
fgets(line,sizeof(line),inputfile);
printf("%s", line);
nlines ++;
fgets(line,sizeof(line),inputfile);
printf("%s", line);
fgets(line,sizeof(line),inputfile);
printf("%s", line);
nlines ++;

//(void)sscanf(line,"%d %d %d %d %d %d %d %d %d %d %d %d %f %d %d %f %f %f %f %f %d %f %f %f %f %f %f %f %f %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %f %f %f %f %f %f %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f",&SDId,&AugerID,&GPSSec,&GPSNSec,&BadPeriod,&YYMMDD,&HHMMSS,&TelEvtBits,&TelDAQBits,&MoonCycle,&RecLevel,&Npix,&SDPTheta,&SDPThetaErr,&SDPPhi,&SDPPhiErr,&SDPChi2,&SDPNdf,&Rp,&RpErr,&Chi0,&Chi0Err,&T0,&T0Err,&TimeChi2,&TimeChi2FD,&TimeNdf,&Easting,&Northing,&Altitude,&NorthingErr,&EastingErr,&RhoNE,&Theta,&ThetaErr,&Phi,&PhiErr,&RhoPT,&RA,&Dec,&RAErr,&DecErr,&RhoRD,&GalLong,&GalLat,&GalLongErr,&GalLatErr,&RhoLL,&dEdXmax,&dEdXmaxErr,&Xmax,&XmaxErr,&X0,&X0Err,&Lambda,&LambdaErr,&GHChi2,&GHNdf,&LineFitChi2,&EmEnergy,&EmEnergyErr,&Energy,&EnergyErr,&MinAngle,&MaxAngle,&MeanAngle,&ChkovFrac,&NTank,&HottestTank,&AxisDist,&SDPDist,&SDFDdt,&XmaxEyeDist,&EyeMaxAtt,&XTrackMin,&XTrackMax,&XFOVMin,&XFOVMax,&XTrackObs,&DegTrackObs,&TTrackObs,&MieDatabase);

//(void)sscanf(line,"%d %d %d %d %d %d %d %f %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %f %f %d %f %f %f %f %f %f",&SDId,&AugerID,&GPSSec,&GPSNSec,&BadPeriod,&YYMMDD,&HHMMSS,&MJD,&T4,&T5,&LDFStat,&Energy,&EnergyErr,&S1000,&S1000Err,&S1000Sys,&Theta,&ThetaErr,&Phi,&PhiErr,&ThetaSite,&PhiSite,&NCand,&NAct,&NWork,&Xcore,&Ycore,&Zcore,&XcoreErr,&YcoreErr,&ZcoreErr,&Easting,&Northing,&RA,&Dec,&RaErr,&DecErr,&GalLat,&GalLong,&GalLatErr,&GalLongErr,&PlaneChi2,&PlaneNdf,&Beta,&BetaErr,&Gamma,&GammaErr,&LDFchi2,&LDFNdf,&RCurv,&RCurvErr,&RiseTime,&RiseTimeErr,&TResMean,&TResSpread);

(void)sscanf(line,"%d %d %d %d %d %f %f %f %f %f %f %f",&specie,&model,&interaction,&fraction,&relativistic,&energy,&v0x,&v0y,&v0z,&rx0,&ry0,&rz0);

//sscanf(line,"%d %d %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ",&Eye,&Run,&Event,&GPSSec,&GPSNSec,&YYMMDD,&HHMMSS,&SDId,&TelEvtbits,&TelDAQbits,&MoonCycle,&Easting,&Northing,&Altitude,&NorthingErr,&EastingErr,&RhoNE,&Theta,&ThetaErr,&Phi,&PhiErr,&RhoPT,&RA,&Dec,&RAErr,&DecErr,&RhoRD,&GalLong,&GalLat,&GalLongErr,&GalLatErr,&RhoLL);

if (nlines == 3){
// Escrevendo no Terminal

	printf("specie=%d \n",specie);
	printf("model=%d \n ",model);
	printf("interaction=%d, fraction=%d \n",interaction, fraction);
	printf("relativistic=%d \n",relativistic);
	printf("energy=%f \n",energy);
	printf("vx=%f vy=%f vz=%f \n",v0x,v0y,v0z);
	printf("r0x=%f r0y=%f r0z=%f \n\n",rx0,ry0,rz0);
}

//(void)fprintf(outfile,"%f %f %f %f %e %f %f %f %f %e\n",RA,Dec,RAErr,DecErr,RhoRD,GalLong,GalLat,GalLongErr,GalLatErr,RhoLL);

//}

fclose(inputfile);

}


/*
	if(i==1){(void)sscanf(line,"%d",&specie);}
	if(i==2){(void)sscanf(line,"%d",&model);}
	if(i==3){(void)sscanf(line,"%d %d",&interaction, &fraction);}
	if(i==4){(void)sscanf(line,"%d",&relativistic);}
	if(i==5){(void)sscanf(line,"%f",&energy);}			
	if(i==6){(void)sscanf(line,"%.15f %.15f %.15f", &v0[0], &v0[1], &v0[2]);}//3
	if(i==7){(void)sscanf(line,"%f %f %f", &r0[0], &r0[1], &r0[2]);}//3

	if((nlines >= 1)&& (nlines < 7 )) {
	// Escrevendo no Terminal

	printf("specie=%d \n",specie);
	printf("model=%d \n ",model);
	printf("interaction=%d, fraction=%d \n",interaction, fraction);
	printf("relativistic=%d \n",relativistic);
	printf("energy=%f \n",energy);
	printf("vx=%f vy=%f vz=%f \n", v0[0], v0[1], v0[2]);
	printf("r0x=%f r0y=%f r0z=%f \n", r0[0], r0[1], r0[2]);
*/	
