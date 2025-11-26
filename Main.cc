// Prog.cc
// This Program is
#include "Main.h"
using namespace std;
using namespace boost::multiprecision;
using namespace std::chrono;


int main (int par_exec1, char* pars_exec[])
{   
 
//Objects creation
	
	auto start = high_resolution_clock::now();
	
	Mathematics * Math = new Mathematics();
	Physics * Phys = new Physics();
 	InputParameters * Input = new InputParameters();
    
 	std::ofstream outfile("Pos.dat"); //Data of the particle positions (x,y,z)
 	std::ofstream outfile2("larmor.dat"); //Data (time,larmor radius)
 	std::ofstream outfile3("mapping.dat"); // Data (x,y,modB)
 	std::ofstream outfile4("data.dat"); //Informations about the initial state of the simulation
 	std::ofstream outfile5("magneticvector.dat"); //Data (x,y,Bx,By)
 	std::ofstream outfile6("plane.dat"); //Particle data positions (x,y,z), in the plane
 	std::ofstream outfile9("desvio.dat"); //Descreve o desvio da partícula no espaço.
 	std::ofstream outfile10("deflection.dat"); //Recebe a direção de saída (da Terra e do Halo) da partícula.
	
	srand(time(NULL));	
     	randomic=Math->random();
    
	///////////////////////////////////////////Calling the variables//////////////////////////////////

        Input->ReadingInputParameters(specie,model,turbulence,mapping,energy,passo,rx0,ry0,rz0);
    
        std::cout << "specie=" << specie << ", model=" << model << ", Turbulence=" << turbulence << ", Mapping=" << mapping << " \n";
          
	std::cout << std::scientific << std::setprecision(6);
	std::cout << "energy=" << energy << ", passo=" << passo << " \n";
	
	std::cout << std::setprecision(3);
	std::cout << "r0x=" << rx0 << ", r0y=" << ry0 << ", r0z=" << rz0 << " \n\n";
    
	///////////////////////////////////////Begin of the program////////////////////////////////////
	
    	printf("*******PROPAGATION OF COSMIC RAYS*******\n\n");  

	//Definindo a massa e a carga da particula:
			
		m_0=m_v[specie]*m_p; //Rest mass of a particle
		q=-q_v[specie]*qe; //Adicionei o sinal de - para fazer o Backtraking
		modq = -q;
		
	//Definindo os parâmetros para calcular médias:
	
		meanB[0]=0;
		
		meanB[1]=0;
		
		meanB[2]=0;
		
		modmeanB=0;
		
	//Modificando a entrada inicial do programa:
	
		//Definindo a posição inicial que entrou no programa (em kpc):
		
			r0[0]=rx0;
			r0[1]=ry0;
			r0[2]=rz0;
			
			std::cout << std::scientific <<std::setprecision(6);
			std::cout << "x =" << r0[0] << ",y =" << r0[1] << ",z =" << r0[2]<< std::endl;

		//Convertendo a energia inicial de eV para J:
	
			energy=energy*qe;
		
		//Calculando o modulo da velocidade inicial e suas componentes:
			
			//std::cout << std::scientific << std::setprecision(6);
			//std::cout << "E =" << energy << ",modv =" << modv << ",c = " << c << ", m_0 = " << m_0 << "\n";
			
			Phys->Ener2vel(energy,modv,c,m_0); //Encontramos o módulo da velocidade
			
			//std::cout << std::scientific << std::setprecision(20) << "modv=" << modv << "\n";
			
		//Sorteando os ângulos esféricos:
		
			rand1=Math->random();
			
			//Corigindo para abranger toda a latitude
			Types::float_precision cos_theta = 2.0 * rand1 - 1.0;
			theta1=acos(cos_theta);
			Types::float_precision sin_theta = sqrt(1.0-cos_theta*cos_theta);
		
			rand2=Math->random();
			phi1=rand2*2*constants::pi;
			
			//std::cout << std::scientific << std::setprecision(6) << "theta1 =" << theta1/constants::rad2deg << ",phi1 =" << phi1/constants::rad2deg <<std::endl;
			//std::cout << "rand1 = " << rand1 << ",rand2 = " << rand2 << "\n";
			
		//Usando os ângulos aleatórios para calcular as componentes na mudança esférico -> Cartesiano
		
			v0[0]=modv*sin_theta*cos(phi1);
			v0[1]=modv*sin_theta*sin(phi1);
			v0[2]=modv*cos_theta;
			
			modv=Math->Mod(v0);
			betavelocity=modv/c;
			
			outfile10 << std::scientific << std::setprecision(20) << modv << " " << theta1*constants::rad2deg << " "<< phi1*constants::rad2deg << "\n";

			//std::cout <<std::scientific <<std::setprecision(20);
			//std::cout << "Vx =" << v0[0] << ",Vy =" << v0[1] << ",Vz =" << v0[2] << std::endl; 
			//std::cout << std::scientific << std::setprecision(20) << "modv=" << modv << "\n";
		
		//Verificando se a velocidade ultrapassou a velocidade da luz:
			
			if(modv>=c){
				
				factor=(0.99999999999999999*c)/modv;
					
				for(k=0;k<=2;k++) v0[k]=v0[k]*factor;
				
				modv=Math->Mod(v0);
				betavelocity=modv/c;
						
			}
			
			//std::cout <<std::scientific <<std::setprecision(20);
			//std::cout << "Vx=" << v0[0] << "Vy=" << v0[1] << "Vz=" << v0[2] << std::endl; 
			//std::cout << std::scientific << std::setprecision(20) << "modv=" << modv << "\n";
			
			if (modv >= c) {
   				std::cout << "VELOCIDADE ULTRAPASSOU A LUZ \n";
    				std::cout << "ANTES DA SIMULACAO PRINCIPAL\n";
				outfile4 << "\n\n*******VELOCIDADE ULTRAPASSOU A LUZ*******\n\n";
    				outfile4 << "\n\n*******ANTES DA SEPARAÇÃO DAS VELOCIDADES*******\n\n";
    				exit(0);
			}

		//Salvando os valores iniciais da velocidade:
		
			V_inicial[0]=v0[0];
			V_inicial[1]=v0[1];
			V_inicial[2]=v0[2];
	
	//Definindo a massa da particula em movimento (Sempre usamos relatividade):
	
		gammaL=Phys->gammafunc(modv,c);
		m=gammaL*m_0; //Relativistic Mass of a particle
	
	//Convertendo a entrada de kpc para metros:
	
		r0[0]=r0[0]/kp;
		r0[1]=r0[1]/kp;
		r0[2]=r0[2]/kp;
		
		modr=Math->Mod(r0);
		
		raio_galac=raio_galac/kp; //convertendo o raio galactico de kpc para metros
		horizontal = sqrt(r0[0]*r0[0]+r0[1]*r0[1]); //calculando a componente horizontal
		vertical = r[2]; //calculando a componente vertical
		
	//Colocando o ponto de partida no gráfico:
	
		outfile << std::scientific << std::setprecision(8) 
		        << r0[0] * kp << " " << r0[1] * kp << " " << r0[2] * kp << "\n";
	
	//Fazendo o print de algumas variáveis:
	
		std::cout << std::scientific << std::setprecision(4);
		std::cout << "r0x=" << r0[0] * kp << " kpc r0y=" << r0[1] * kp << " kpc r0z=" << r0[2] * kp << "\n";
		
		std::cout << std::scientific << std::setprecision(3);
		std::cout << "$E_{inicial}=" << energy / qe << "$ eV, Gamma=" << gammaL << ", m=" << m_0 << "\n";
		
		std::cout << std::scientific << std::setprecision(6) << "Vx=" << v0[0] 
		          << ", Vy=" << v0[1] << ", Vz=" << v0[2] 
		          << std::setprecision(15) << ", modv=" << modv 
		          << std::setprecision(17) << ", beta=" << betavelocity << "\n \n";
		
		std::cout << std::scientific << std::setprecision(6);
		std::cout << "horizontal=" << horizontal * kp << ", raio_galac=" << raio_galac * kp << "\n";
	
	
	//Definindo algumas condições iniciais do campo magnético galáctico:

		std::cout << "******CAMPO GALACTICO*******\n\n";
    	
    	//Calculando campo magnético inicial:
    		
    		if(model==0){
				Phys->GalacticASS(BG,r0); 
			}
			if(model==1){
				Phys->GalacticBSS(BG,r0); 
			}
			
  			modB=Math->Mod(BG);
  		
			std::cout << std::scientific << std::setprecision(6);
			std::cout << "B0x=" << BG[0] << ", B0y=" << BG[1] << ", B0z=" << BG[2] << "\n";
			
		//Algumas características do movimento:
			
    		Phys->Angvelocity(w,modq,modB,m);
    		
    		Phys->period(T,w);
		
		//Definindo a posição da partícula em kpc:
		
			modrkpc=modr*kp;
			
		//Informações Iniciais
		
			v_inicial=modv;
			r_inicial=modr*kp;	
			
///////////////////MAGNETIC MAPPING FUNCTIONS/////////////////

	if(mapping==1){
	
		Phys->mappingxy(posx,posy,model);
		exit(0);
	
	}

	if(mapping==2){
	
		Phys->mappingcircular(radiusG,thetaG,model);
		exit(0);
	
	}	

//////////////////////// MAIN LOOP (Galatic Magnetic Field) ////////////////////////////

	while(modrkpc<=galac_sphere_raio){ 
	 
		//Initial Conditions:
		
			modr=Math->Mod(r0);
			
			counter=counter+1;
			
			//Adicionando o tempo do movimento a cada passo:
			
				t_passo=time_factor*T;
				
			
			//Corrigindo o tempo de passo com limites:
			
				if (t_passo > dt_max) {
   				
    				t_passo = dt_max;
				} 
				
				if (t_passo < dt_min) {
    			
    				t_passo = dt_min;
				} 
			
			travel_time += t_passo;
		
		//Calculating the Galatic Field (BG):
		
			if(model==0){
				Phys->GalacticASS(BG,r0); 
			}
			if(model==1){
				Phys->GalacticBSS(BG,r0); 
			}

			modB=Math->Mod(BG);
			
		//Applying the turbulence:
		
			//std::cout << std::scientific << std::setprecision(18) << "Bx = " << BG[0] << ",By = " << BG[1] << ",Bz = " << BG[2] << "\n";
		
			if(turbulence==0){
				Phys->turbulence(BGT,BG);
				for(k=0;k<=2;k++){	
						BG[k]=BGT[k];	
				}
			}
			

		//Calculating the mean magnetic field:
		
			for(k=0;k<=2;k++){		
					meanB[k]=meanB[k]+BG[k];
					
			}	
			modmeanB=modmeanB+modB;
			
		//Calculantig the relativistic particle mass:
		
			Phys->Relat(m,m_0,v0); 
															
		//Making the projections of velocity:
		
			Math->Projections(vpar,vper,v0,BG);
			
			modv0=Math->Mod(v0);
			modvpar=Math->Mod(vpar);
			modvper=Math->Mod(vper);
			
		//Intrinsic characteristics:
	
			Phys->Larmor(rL,m,modq,modvper,modB);
			Phys->Angvelocity(w,modq,modB,m);
			Phys->period(T,w);
			Phys->Pitch(vper,vpar);
			
		//Calculating the Lorentz force and aceleration:
		
			Phys->FLorentz(F,q,vper,BG);
			Phys->accelerationRelativity(a,F,v0,m_0);
				
		//Using the basics formules of the moviment:
			
			Phys->Velocity(v,vper,a,t_passo); 
			
			for(k=0;k<=2;k++) vpera[k]=v[k];

			for(k=0;k<=2;k++) v[k]=vpera[k]+vpar[k];
			
			
			modv=Math->Mod(v);
	
		//Corrigindo velocidades maiores que a da luz:

			if(modv>=c){
					
				factor=(0.9999999999999999*c)/modv;
					
				for(k=0;k<=2;k++) v[k]=v[k]*factor;
						
			}
			
			modv=Math->Mod(v); 
				
		//Calculating the position
			
			Phys->Trajectory(r,r0,v0,a,t_passo);
	
			outfile << std::scientific << std::setprecision(8) << r[0] * kp << " " << r[1] * kp << " " << r[2] * kp << "\n";
			
		//Calculando o desvio da tragetória:
		
			cos_theta = (v0[0]*v[0]+v0[1]*v[1]+v0[2]*v[2])/(modv0*modv);
			
			if (cos_theta > 1.0) cos_theta = 1.0;
            		if (cos_theta < -1.0) cos_theta = -1.0;
			
			desvio_rad= acos(cos_theta);
			desvio_grau = desvio_rad*constants::rad2deg;
			
			desvio_grau0 = desvio_grau0 + desvio_grau;
			
			outfile9 << std::scientific << std::setprecision(10) << travel_time << " " << std::setprecision(10) << desvio_grau0 << " " << desvio_grau << "\n";
			
		//Definindo as novas condições iniciais:
		
			for(k=0;k<=2;k++) {
				v0[k]=v[k];
				r0[k]=r[k];
			}
		
			modr=Math->Mod(r0);
			modrkpc=modr*kp;
			
		//Calculating the beta term:
		
			betavelocity=modv/c;
			gammatest=Phys->gammafunc(modv,c);
		
		//Preparing for the next loop (Some variable prints and test):
			
			//Printing in some of the archives:
			
			outfile2 << std::scientific << std::setprecision(12) << travel_time << " " << rL * kp << "\n";

			//Visualization of the running simulation on the terminal:
			
			//std::cout << "counter = " << counter << std::scientific << std::setprecision(6) << ", modB = " << modB << ", modr =  " << modrkpc << "kpc" << std::setprecision(30) << ", modv = " << modv << "\n";
			//std::cout << std::scientific << std::setprecision(18) << "modv=" << modv << ", beta=" << betavelocity << std::setprecision(6) << ", BGx=" << BG[0] << ", BGy=" << BG[1] << ", BGz=" << BG[2] << ", vx=" << v[0] << ", vy=" << v[1] << ", vz=" << v[2] << "\n";

		//Propagation in the Galatic Plane
		
			//Vertical and Horizontal limits:
			
				horizontal = sqrt(r0[0]*r0[0]+r0[1]*r0[1]);
				vertical = r0[2];
			
				vertical_kpc=vertical*kp;
				horizontal_kpc=horizontal*kp;
			
		//Garantindo agora que os valores que serão analisados para definir o limite do plano são maiores que 0:
		
			if(vertical_kpc<0){
				vertical_kpc = - vertical_kpc;
			}
			if(horizontal_kpc<0){
				horizontal_kpc = - horizontal_kpc;
			}
			
			
			if(horizontal_kpc <= horizontal_limit && vertical_kpc <= vertical_limit){
				outfile6 << std::scientific << std::setprecision(10) << r[0] * kp << " " << r[1] * kp << " " << r[2] * kp << "\n";
			}
			
			if((horizontal_kpc > horizontal_limit || vertical_kpc > vertical_limit) && counter_escape == 0){
    			escape_time = travel_time;
    			counter_escape=counter_escape+1; // Marca que a partícula escapou
			}			
			
		//Definition of some importante variables to display in the end:
		
			if(modv>c){
		
				std::cout << "VELOCIDADE ULTRAPASSOU/IGUALOU A LUZ";
				outfile4 << "\n\n*******VELOCIDADE ULTRAPASSOU A LUZ*******\n\n";
				outfile4 << "\n\n*******DENTRO DO LOOP PRINCIPAL*******\n\n";
				exit(0);
			}

		//Exit terms:
			
		if (modrkpc <= inferior_limit_galaxy) {
    			outfile4 << "\n\n*******REACHE THE GALATIC CENTER*******\n\n";
    			std::cout << "\n\n***********REACHED THE GALATIC CENTER*********\n\n";
    			
			    outfile4 << "\n\n***Program Initial Constants***\n\n";
			    
			    outfile4 << std::fixed << std::setprecision(0);
    			    outfile4 << "specie =" << specie << ", m_0 =" << m_v[specie] << "*m, q =" << q_v[specie] << "*q_e \n ";
    			    
    			    outfile4 << "\n\n***Initial Conditions of the System\n\n";
    			    
    			    outfile4 << std::scientific << std::setprecision(8) << "Energy=" << energy / qe << "\n";
			    outfile4 << std::setprecision(25) << "v_inicial =" << v_inicial / c << "*c m/s \n"; 
			    outfile4 << "V0x=" << V_inicial[1] << " m/s, V0y=" << V_inicial[2] << " m/s, V0z=" << V_inicial[3] << " m/s \n"; 
			    outfile4 << std::setprecision(8) << "modr_initial =" << r_inicial << " kpc \n";  

			    outfile4 << "\n\n Propagation Characteristics \n\n";		   
    			
    			    outfile4 << std::setprecision(8) << "Tempo de propagacao =" << travel_time << " s =" << (travel_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << std::setprecision(10) << "Escape_time (plane)=" << escape_time << " s=" << std::setprecision(6) << (escape_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << "Valores medios: Bx=" << meanB[0] / counter << " T, By=" << meanB[1] / counter << " T, Bz=" << meanB[2] / counter << " T, meanB=" << modmeanB / counter << " T \n";
    			    

			    outfile4 << "****DON'T ESCAPE THE HALO**** \n";
			    auto stop = high_resolution_clock::now();
			    auto duration = duration_cast<minutes>(stop - start);
			    std::cout <<"Simulation Time (min): " << duration.count() << endl;
			    std::cout << endl;
			    
			    
			    outfile4 << std::fixed << std::setprecision(0) << "Tempo da Simulação (min):" << duration.count() << "\n";
			    
			    outfile.flush();
			    outfile2.flush();
			    outfile3.flush();
			    outfile4.flush();
			    outfile5.flush();
			    outfile6.flush();
			    outfile9.flush();
			    outfile10.flush();
 
			    exit(0);
		}

		if (counter == 1200000) {
			    outfile4 << "\n\n*******REACHE THE COUNTER MAXIMUM*******\n\n";
			    std::cout << "\n\n*******REACHE THE COUNTER MAXIMUM*******\n\n";
			    
			    outfile4 << "\n\n***Program Initial Constants***\n\n";
			    
			    outfile4 << std::fixed << std::setprecision(0);
    			    outfile4 << "specie =" << specie << ", m_0 =" << m_v[specie] << "*m, q =" << q_v[specie] << "*q_e \n ";
    			    
    			    outfile4 << "\n\n***Initial Conditions of the System\n\n";
    			    
    			    outfile4 << std::scientific << std::setprecision(8) << "Energy=" << energy / qe << "\n";
			    outfile4 << std::setprecision(25) << "v_inicial =" << v_inicial / c << "*c m/s \n"; 
			    outfile4 << "V0x=" << V_inicial[1] << " m/s, V0y=" << V_inicial[2] << " m/s, V0z=" << V_inicial[3] << " m/s \n"; 
			    outfile4 << std::setprecision(8) << "modr_initial =" << r_inicial << " kpc \n";  

			    outfile4 << "\n\n Propagation Characteristics \n\n";		   
    			
    			    outfile4 << std::setprecision(8) << "Tempo de propagacao =" << travel_time << " s =" << (travel_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << std::setprecision(10) << "Escape_time (plane)=" << escape_time << " s=" << std::setprecision(6) << (escape_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << "Valores medios: Bx=" << meanB[0] / counter << " T, By=" << meanB[1] / counter << " T, Bz=" << meanB[2] / counter << " T, meanB=" << modmeanB / counter << " T \n";
    			    

			    outfile4 << "****DON'T ESCAPE THE HALO**** \n";
			    auto stop = high_resolution_clock::now();
			    auto duration = duration_cast<minutes>(stop - start);
			    std::cout <<"Simulation Time (min): " << duration.count() <<endl;
			    
			    outfile4 << std::fixed << std::setprecision(0) << "Tempo da Simulação (min):" << duration.count() << "\n";
			    
			    outfile.flush();
			    outfile2.flush();
			    outfile3.flush();
			    outfile4.flush();
			    outfile5.flush();
			    outfile6.flush();
			    outfile9.flush();
			    outfile10.flush();
 	
			    exit(0);
		}
							
			
		}
		
		Math->Cart2Esf(deflection,r0);
		
		outfile10 << std::scientific << std::setprecision(20) << deflection[0]*kp << " " << deflection[1]*constants::rad2deg << " "<< deflection[2]*constants::rad2deg << "\n";
			

		outfile4 << "\n\n**********ESCAPE THE GALATIC HALO**********\n\n";
		
		std::cout << "\n\n**********ESCAPE THE GALATIC HALO**********\n\n";
		
			    outfile4 << "\n\n***Program Initial Constants***\n\n";
			    
			    outfile4 << std::fixed << std::setprecision(0);
    			    outfile4 << "specie =" << specie << ", m_0 =" << m_v[specie] << "*m, q =" << q_v[specie] << "*q_e \n ";
    			    
    			    outfile4 << "\n\n***Initial Conditions of the System\n\n";
    			    
    			    outfile4 << std::scientific << std::setprecision(8) << "Energy=" << energy / qe << "\n";
			    outfile4 << std::setprecision(25) << "v_inicial =" << v_inicial / c << "*c m/s \n"; 
			    outfile4 << "V0x=" << V_inicial[1] << " m/s, V0y=" << V_inicial[2] << " m/s, V0z=" << V_inicial[3] << " m/s \n"; 
			    outfile4 << std::setprecision(8) << "modr_initial =" << r_inicial << " kpc \n";  

			    outfile4 << "\n\n Propagation Characteristics \n\n";		   
    			
    			    outfile4 << std::setprecision(8) << "Tempo de propagacao =" << travel_time << " s =" << (travel_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << std::setprecision(10) << "Escape_time (plane)=" << escape_time << " s=" << std::setprecision(6) << (escape_time) / (3.15 * pow(10, 7)) << " anos \n";
    			    outfile4 << "Valores medios: Bx=" << meanB[0] / counter << " T, By=" << meanB[1] / counter << " T, Bz=" << meanB[2] / counter << " T, meanB=" << modmeanB / counter << " T \n";
			    
			    auto stop = high_resolution_clock::now();
			    auto duration = duration_cast<minutes>(stop - start);
			    std::cout <<"Simulation Time (min): " << duration.count() <<endl;
			    outfile4 << std::fixed << std::setprecision(0) << "Tempo da Simulação (min):" << duration.count() << "\n";
 	
	//system("pause");
	return 0;
}
