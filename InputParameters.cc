#include <cstdlib>
#include <string>     
#include <fstream>    
#include <sstream>    
#include <iostream>

//local headers/
#include "InputParameters.h"
#include "types.h"

using namespace std;
using namespace boost::multiprecision;

//InputParameters.cc/

//constructor of the class/
InputParameters::InputParameters ( ){

}

//destructor of the class/
InputParameters::~InputParameters ( ){

}


//methods of the Input Parameters class

                                             
void InputParameters::ReadingInputParameters(int& specie, int& model, int& turbulence, int& mapping, Types::float_precision& energy,Types::float_precision& passo, Types::float_precision& rx0, Types::float_precision& ry0, Types::float_precision& rz0){//1 
 	
std::ifstream inputFile("input.dat");
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file input.dat\n";
        exit(EXIT_FAILURE);
    }

    // 2. Ler o ficheiro linha por linha
    while (std::getline(inputFile, line)) {
        // Ignorar linhas de comentário ou vazias
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // 3. Usar um stringstream para extrair os valores da linha
        std::stringstream ss(line);
        ss >> specie >> model >> turbulence >> mapping >> energy >> passo >> rx0 >> ry0 >> rz0;

        // Verificação de erro opcional, mas recomendada
        if (ss.fail()) {
            std::cerr << "Error: Failed to parse line in input file: " << line << "\n";
        }
        
        std::cout << "specie=" << specie << ", model=" << model << ", Turbulence=" << turbulence << ", Mapping=" << mapping << " \n";
          
	std::cout << std::scientific << std::setprecision(6);
	std::cout << "energy=" << energy << ", passo=" << passo << " \n";
	
	std::cout << std::setprecision(3);
	std::cout << "r0x=" << rx0 << ", r0y=" << ry0 << ", r0z=" << rz0 << " \n\n";

        // Como só queremos ler uma linha de dados, paramos o loop
        break;
    }

    // 4. O ficheiro é fechado automaticamente quando 'inputFile' sai de escopo.
    // Nenhuma chamada a fclose() é necessária.
}

