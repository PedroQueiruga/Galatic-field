// Prog.cc
// This Program is


#include "Main.h"

int main (int par_exec1, char* pars_exec[])
{   
 
//Objects creation

	Mathematics * Math = new Mathematics();
    Physics * Phys = new Physics();
    InputParameters * Input = new InputParameters();
    
	FILE * outfile;
	outfile = fopen("Positions.dat","w");
	
	FILE * outfile2;
	outfile2 = fopen("larmor.dat","w");
	
	FILE * outfile3;
	outfile3 = fopen("Magnetic.dat","w");
	
	FILE * outfile4;
	outfile4 = fopen("ridity_position.dat","w");

    printf("*******PROPAGATION OF COSMIC RAYS*******\n\n");
	
	//Podemos setar uma variavel model=0,1,2,3. Onde 0:Campo uniforme, 1:campo variavel 1/r, 2:campo de dipolo, 3:campo galactico   
	//Input->ReadingInputParameters(specie,model,interaction,fraction,relativistic,energy,v0x,v0y,v0z,rx0,ry0,rz0);

	//Definindo a massa e a carga da particula:
			
		m_0=m_v[specie]*m; //Rest mass of a particle
		q=q_v[specie]*qe;
		
	//Modificando a entrada inicial do programa:

	//Convertendo de eV para J:
	
		energy=energy*qe;
		
	//Calculando o modulo da velocidade inicial e suas componentes:
		
		modv=Phys->Ener2vel(energy,modv,c,m_0);
		
		v0[0]=1.0/3.0*c;
		v0[2]=0;
		v0[1]=sqrt(modv*modv-v0[0]*v0[0]); // O módulo de v deve ser maior do que o vx;
	
		initialy=v0[1];
	
	//Verificando o angulo de entrada de acordo com as componentes da velocidade:
	
		phi0=atan(v0[1]/v0[0]);
		
		if(phi0>=0){
				
			phi0=phi0;
			
		}
			
		if(phi0<=0){
				
			phi0=-phi0;
			
		}
	
		if(v0[0]<0 && v0[1]>0){
		
			phi0=phi0+1.5708;
			
		}
		
		if(v0[0]<0 && v0[1]<0){
		
			phi0=phi0+3.14159;		
		}
		
		if(v0[0]>0 && v0[1]<0){
		
			phi0=phi0+4.71239;	
		}
	
	printf("Theta=%.6e graus \n",phi0*57.2958);
	
	//Definindo a massa da particula em movimento:
	
	gamma=Phys->gammafunc(modv,c);
	m=gamma*m_0; //Relativistic Mass of a particle
	
	
	//Convertendo a entrada de kpc para metros:

		r0[0]=r0[0]/kp;
		r0[1]=r0[1]/kp;
		r0[2]=r0[2]/kp;
		raio_galac=raio_galac/kp;
		galac_sphere_raio=galac_sphere_raio/kp;
	
	//printf("( r0x=%.6e r0y=%.6e r0z=%.6e ) m\n",r0[0],r0[1],r0[2]);
	
	printf("$E_{inicial}=%.3e$ eV, Gamma=%.3e, m=%.3e \n",energy/qe,gamma,m_0);
	printf("Vx=%.6e, Vy=%.6e, Vz=%.6e, modv=%.6e \n \n", v0[0], v0[1], v0[2],modv);
	
	//m_0=gamma*m_v[specie]*m;
	//q=q_v[specie]*qe;
	
	horizontal = sqrt(r0[0]*r0[0]+r0[1]*r0[1]);
	
	//printf("horizontal=%.6e, raio_galac=%.6e \n",horizontal,raio_galac);
	
	//Efeitos relativisticos:
	
	/*
	if(relativistic==0){
		
		for(i=0;i<=2;i++){
			v0[i]=c*v0[i];
		}
		
		modv=Math->Mod(v0);	
		
		gamma=Phys->gammafunc(modv,c);
		
		m_0=m_v[specie]*m; //Rest mass of a particle
		q=q_v[specie]*qe;
		m=gamma*m_0; //Relativistic Mass of a particle
		
		//energy=m_0*c*c;
		
		printf("$E_{inicial}=%.3e$ J, Gamma=%.3e, m=%.3e \n",energy/qe,gamma,m_0);
	
	}
	*/
	
	if(relativistic==1){
		
		Phys->Ener2vel(energy,modv,c,m);
		
		for(i=0;i<=2;i++){
			
			v0[i]=modv*v0[i];
			
		}
		
		v0[2]=1-sqrt(1-v0[0]*v0[0]-v0[1]*v0[1]);
	
	}
	
	modr=Math->Mod(r0);
	
	//Condicoes iniciais para os modelos trabalhados:
		
	if(model<3)
	{
		
		//v0[0]=c/3,v0[1]=c/3,v0[2]=c/15;
    	B0[0]=0,B0[1]=0,B0[2]=1e-4;
    	
		//Modules and larmor:
	
    	modv=Math->Mod(v0);	
		printf("modv0=%.10e m/s = %.4f*c \n",modv,modv/c);
	
		modB=Math->Mod(B0);
		printf("B0=%.3e T = %.3e G\n",modB,modB/1E-4);
	
		rL0=Phys->Larmor(rL,m_0,q,modv,modB);
		printf("rL=%.3e m = %.3e UA\n\n",rL0,rL0/UA);
		
		printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r0[0],r0[1],r0[2]);
		
		x_max=r0[0]+10*rL0,y_max=r0[1]+10*rL0,z_max=r0[2]+10*rL0;
		x_min=r0[0]-10*rL0,y_min=r0[1]-10*rL0,z_min=r0[2]-0*rL0;

    	//x_max=O[0]+10*rL0,y_max=O[1]+10*rL0,z_max=O[2]+10*rL0;
		//x_min=O[0]-10*rL0,y_min=O[1]-10*rL0,z_min=O[2]-0*rL0;
		
		r[3]=z_min;
		
		fprintf(outfile,"%.3e %.3e %.3e %.3e %.3e %.3e\n",x_min/UA,y_min/UA,z_min/UA,x_max/UA,y_max/UA,z_max/UA); //Give the max and minimum values
    	
    	//Testando qual o modelo esta sendo chamado:
		printf("model=%d \n",model);
    	
		if(model==0) printf("*******CAMPO UNIFORME*******\n\n");
		
    	if(model==1) printf("*******CAMPO VARIAVEL*******\n\n");
    	
    	if(model==2) printf("*******CAMPO DIPOLAR*******\n\n");
	}
    else
	{
    	printf("******CAMPO GALACTICO*******\n\n");
    
  		Phys->Galactic(B0,r0);
		  
		//printf("B0x=%.6e, B0y=%.6e, B0z=%.6e \n",B0[0],B0[1],B0[2]);  
  		
		printf("v0x=%.6e, v0y=%.6e, v0z=%.6e \n",v0[0],v0[1],v0[2]);

		x_max=r0[0]+0.24*rs,y_max=r0[1]+0.24*rs,z_max=r0[2]+0.24*rs;
		x_min=r0[0]-0.24*rs,y_min=r0[1]-0.24*rs,z_min=r0[2]-0*rs;
		
		//A espessura da galaxia:0.05 kpc
		//To Increase the zoom: 0.1 --> 0.01
		//To decrease the zoom: 0.1 --> 0.8
		
			//Modules and larmor:
	
   	 	modv=Math->Mod(v0);	
		printf("modv0=%.10e m/s = %.4f*c \n",modv,modv/c);
	
		modB=Math->Mod(B0);
		printf("B0=%.3e T = %.3e G\n",modB,modB/1E-4);
	
		rL0=Phys->Larmor(rL,m_0,q,modv,modB);
		printf("rL=%.3e m = %.3e UA\n\n",rL0,rL0*kp);
		
		modr=Math->Mod(r0);
		
		r[3]=z_min;
		
    	fprintf(outfile,"%.3e %.3e %.3e %.3e %.3e %.3e\n",x_min*kp,y_min*kp,z_min*kp,x_max*kp,y_max*kp,z_max*kp); //Give the max and minimum values
	
	}

    w=Phys->Angvelocity(w,q,modB,m_0);
    T=Phys->period(T,w);
    t=T/fraction; 

    //printf("w=%.6e rad/s, t=%.6e s, T=%.6e s\n",w,t,T);
		
	modr=Math->Mod(r0);

//	LOOP PRINCIPAL

	if(model<3){
		
		//	while(modr<=rs) #Used for the galatic model, where rs is the radius of sun orbit.
		for(i=1;i<=interaction;i++)
		{
			modr=Math->Mod(r0);	
		
			counter=counter+1;
		
			printf("counter=%d, r=%.4e, B=%.4e, rL=%.4e \n",counter,modr,modB, rL);
		
			if(counter<=30) printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r0[0],r0[1],r0[2]);
			
			//Makes the uniform field
			if(model==0){
				
				modB=Math->Mod(B0);
				for(k=0;k<=2;k++) B[k]=B0[k];
		
			}
			
			//Makes the variable field
			if(model==1){
				
				Phys->VarB(B,B0,r0,rL0);
				modB=Math->Mod(B);
		
			}
			
			//Makes the dipolar field
			if(model==2){
				
				Phys->Dip(BD,r0);  
				modB=Math->Mod(BD);
				for(k=0;k<=2;k++) B[k]=BD[k];
					
			}
			
			if(relativistic==1){
				
				m_0=Phys->Relat(m,m_0,v0); //Calculate the relativistic mass
				
			}
			 
			if(counter<=30) printf("m_0=%.4e \n",m_0);
		
			Math->Projections(vpar,vper,v0,B);
		
			if(counter<=30) printf("modB=%.6e\n",modB);
		
			modvpar=Math->Mod(vpar);
			modvper=Math->Mod(vper);
			
			//if(counter<=30)	printf("modvper=%.6e, modvpar=%.6e \n",modvper,modvpar); 
		
			rL=Phys->Larmor(rL,m_0,q,modvper,modB);		
			//if(i<=30)	printf("B=%.16e, rL=%.16e \n",modB,rL);
			w=Phys->Angvelocity(w,q,modB,m_0);
			//vol=(w*t*i)/(2*pi);
			T=Phys->period(T,w);
			
			if(counter<=30) printf("T=%.6e, w=%.6e, rL=%.6e \n",T,w,rL);
		
			fprintf(outfile2,"%.3e %.3e %.3e\n",t*counter,rL*kp,T); //tempo, raio de larmor, voltas
		
			angle=Phys->Pitch(vper,vpar);
				
			if(counter<=30) printf("angle=%.16e \n",angle);
		
			Phys->FLorentz(F,q,vper,B); //Chama a função, passa os valores com os nomes que eu utilizo.
		
			for(k=0;k<=2;k++) {
				a[k]=F[k]/m;
			}
		
			Phys->kineticEnergy(K,modv,m_0);
			
			if(counter<=30) printf("K=%.6e \n", K);
			
			Phys->rigidity(Ri,modB,rL);
			
			if(counter<=30) printf("Ri=%.6e \n", Ri);
			
			fprintf(outfile3,"%.3e %.3e\n",Ri,K);
			
			Phys->Velocity(v,vper,a,t); 
		
			if(counter<=30) printf("vX=%.6e vY=%.6e vZ=%.6e\n",v[0],v[1],v[2]);
		
			modv=Math->Mod(v); 
	
			for(k=0;k<=2;k++) v[k]=v[k]+vpar[k];
		
			Phys->Trajectory(r,r0,v0,a,t);
		
	//		if(i<=30) printf("rX=%.6e rY=%.6e rZ=%.6e\n",r[0],r[1],r[2]);
	
  			fprintf(outfile,"%.3e %.3e %.3e \n", r[0]/UA,r[1]/UA,r[2]/UA);

		
			for(k=0;k<=2;k++) {
			v0[k]=v[k];
			r0[k]=r[k];
			}
				
		}//fim do loop principal
	}
	//Galatic magnetic field loop:
	else{
		
		while(modr<=galac_sphere_raio) { //Used for the galatic model, where rs is the radius of sun orbit.
		
		//Initial Conditions:
		
			modr=Math->Mod(r0);
			
			counter=counter+1;
			
			//t_passo=counter*passo;
			
			t_passo=passo;
			
		//Making the modulos of z component:
			
			if(r0[2]>=0){
				
				vertical=r0[2];
			
			}
			
			if(r0[2]<=0){
				
				vertical=-r0[2];
			
			}
				
		//Calculating the time to leave the galaxy disk:
		
		/*	
			if(vertical>=espessura_galac/2){ //Used for calculate the time to leave the galatic halo.
				
				if(count2==0){
					
					printf("***********ESCAPE FROM GALATIC*********** \n \n");
					//printf("Tempo necessario=%.6e s",t*counter);
					
					t_escape=t_passo*counter; //Time to escape	
					
					printf("t_escape=%.6e \n", t_escape);
		
				}
				
				count2=count2+1;
				
				//exit(0); //Use this if you want to exit the program after the particle leave the galaxy disk
				
			}
		*/

		//Analysing the system:
		
			//printf("passo=%.3e \n",passo);
			
			//if(counter<=10) printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r0[0],r0[1],r0[2]);
			
			//printf("counter=%d, r=%.4e, horizontal=%.6e, module=%.4e \n",counter, modr,horizontal,module);
		
		//Makes the galactic field, uses BG:
		
			Phys->Galactic(BG,r0); 
		
			if(counter<=10) printf("BGx=%.6e, BGy=%.6e, BGz=%.6e \n",BG[0],BG[1],BG[2]);
		
			modB=Math->Mod(BG);
			
			Math->Cart2Cyl(p0,r0);
			
			modp0=Math->Mod(p0);
			
			//printf("BG=%.3e \n", BG);
			
			//printf("BGx=%.6e, BGy=%.6e, BGz=%.6e \n",BG[0],BG[1],BG[2]);
			
			fprintf(outfile3,"%.3e %.3e \n",modB,modp0*kp);
			
			//printf("|B|=%.6e T \n",modB);
															
															
																	
		//Making the projections of velocity:
		
			Math->Projections(vpar,vper,v0,BG);
		
			modvpar=Math->Mod(vpar);
			modvper=Math->Mod(vper);
		
		//Basic values of the moviment:
		
			rL=Phys->Larmor(rL,m,q,modvper,modB);		
			w=Phys->Angvelocity(w,q,modB,m);
			T=Phys->period(T,w);
		
			fprintf(outfile2,"%.3e %.3e %.3e\n",t_passo*counter,rL*kp,T); //tempo, raio de larmor, voltas
		
			angle=Phys->Pitch(vper,vpar);
				
			//if(counter<=30) printf("T=%.6e, w=%.6e, rL=%.6e, angle=%.6e, modB=%.6e \n",T,w,rL,angle,modB);
			
		//Calculating the Lorentz force and aceleration:
		
			Phys->FLorentz(F,q,vper,BG); //Chama a funcao, passa os valores com os nomes que eu utilizo.
		
			for(k=0;k<=2;k++) {
				a[k]=F[k]/m;
			}
	
		//Using the basics formules of the moviment:
		
			Phys->Velocity(v,vper,a,t_passo); 
		
			//if(counter<=30) printf("vX=%.6e vY=%.6e vZ=%.6e\n",v[0],v[1],v[2]);
			
			for(k=0;k<=2;k++) v[k]=v[k]+vpar[k];
			
			modv=Math->Mod(v);
			
			Phys->Trajectory(r,r0,v0,a,t_passo);
			
			fprintf(outfile,"%.3e %.3e %.3e \n",r[0]*kp,r[1]*kp,r[2]*kp);
			
			for(k=0;k<=2;k++) {
				v0[k]=v[k];
				r0[k]=r[k];
			}
		
			modr=Math->Mod(r0);
			
		//Rigidity and kinetic energy:
		
			//Phys->kineticEnergy(K,modv,m_0);
			//Phys->rigidity(Ri,modB,rL);
			
			if(relativistic==1){
				
				gamma=Phys->gammafunc(modv,c);
				
				K=m*c*c*(gamma-1);
				
			}
			
			if(relativistic==0){
				
				K=(m_0*modv*modv)/2;
				
			}
			
			
			Ri=modB*rL;	
			
			fprintf(outfile4,"%.3e %.3e %.3e %.3e \n",Ri,r[0]*kp,r[1]*kp,r[2]*kp);
			
		//Calculating the energy:
		
		/*
		gamma=Phys->gammafunc(modv,c);
		
		energy=sqrt((gamma*m_0*modv)*(gamma*m_0*modv)*c*c+m_0*m_0*c*c*c*c);
		*/
			
		//Preparing for the next loop:
		
			horizontal = sqrt(r0[0]*r0[0]+r0[1]*r0[1]);
			
			printf("counter=%d, r=%.4e, horizontal=%.6e, vertical=%.4e, |B|=%.3e \n",counter, modr,horizontal*kp,vertical,modB);
		
		//Definition of some importante variables to display in the end:
		
			if(counter==1){
			
				v_inicial=modv;
				r_inicial=rL*kp;	
			
			}
			
		//Exit terms:
		
			/*
			if(modr>=rs){
				printf("\n\n*******REACHED THE SUN ORBIT*******\n\n"); 
				printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
				printf("v_inicial=%.3f*c m/s, r_inicial=%.3e kpc, t_escape=%.6e s = %.6e anos, Ri=%.2e Tm, Phi0= %.3e graus \n",v_inicial/c, r_inicial,t_escape, t_escape/(3.15*pow(10,7)), Ri, phi0*57.2958);
				printf("V0y=%.6e \n", initialy);
				exit(0);
			}
			*/
	
			/*
			if(vertical>=espessura_galac/2){
				printf("\n\n*******REACHED THE SUPERIOR GALATIC LIMIT*******\n\n"); 
				printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
				printf("v_inicial=%.16f*c m/s, r_inicial=%.3e kpc, t_escape=%.6e s = %.6e anos, Ri=%.2e Tm, Phi0= %.3e graus \n",v_inicial/c, r_inicial,t_escape, t_escape/(3.15*pow(10,7)), Ri, phi0*57.2958);
				printf("V0y=%.6e, Energy=%.6e \n",initialy,energy/qe);
				exit(0);
			}
			*/
			
			if(counter==1200000){
				printf("\n\n*******REACHE THE COUNTER MAXIMUM*******\n\n"); 
				printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
				printf("v_inicial=%.16f*c m/s, r_inicial=%.3e kpc, t_escape=%.6e s = %.6e anos, Ri=%.2e Tm, Phi0= %.3e graus \n",v_inicial/c, r_inicial,t_escape, t_escape/(3.15*pow(10,7)), Ri, phi0*57.2958);
				printf("V0y=%.6e, Energy=%.6e \n",initialy,energy/qe);
				exit(0);
			}
			
			/*
			if(counter==2){
				printf("Phi=%.3e graus, B0 = %.4e T", phi0*57.2958, modB);	
			}
			*/
			
		}
		
	}
	
	printf("\n\n*******REACHE THE HORIZONTAL GALATIC LIMIT*******\n\n"); 
	printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
	printf("v_inicial=%.16f*c m/s, r_inicial=%.3e kpc, t_escape=%.6e s = %.6e anos, Ri=%.2e Tm, Phi0= %.3e graus \n",v_inicial/c, r_inicial,t_passo*counter, (t_passo*counter)/(3.15*pow(10,7)), Ri, phi0*57.2958);
	printf("V0y=%.6e, Energy=%.6e \n",initialy,energy/qe);
	

	fclose(outfile4);
	fclose(outfile3);
	fclose(outfile2);
	fclose(outfile);
    printf("\n\n*******END OF RUN*******\n\n");
 	
	system("pause");
	return 0;
}
