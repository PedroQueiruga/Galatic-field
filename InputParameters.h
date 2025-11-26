// System Headers

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

#include "types.h"

using namespace boost::multiprecision;

class InputParameters
{
private:
	//float_precision ;
public:

//! Constructor of the class.
InputParameters ( ); 

//! Destructor of the class.
~InputParameters ( );

//methods of the Summary class/
void ReadingInputParameters(int& specie, int& model, int& turbulence, int& mapping, Types::float_precision& energy,Types::float_precision& passo, Types::float_precision& rx0, Types::float_precision& ry0, Types::float_precision& rz0);
};

