
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>


class InputParameters
{
private:
	//double ;
public:

//! Constructor of the class.
InputParameters ( ); 

//! Destructor of the class.
~InputParameters ( );

//methods of the Summary class/
void ReadingInputParameters(int specie,int model,int interaction,int fraction,int relativistic,float energy,float v0x,float v0y,float v0z,float rx0,float ry0,float rz0);
//float CheckingInputParameters();

};

