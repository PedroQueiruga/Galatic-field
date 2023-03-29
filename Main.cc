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
	outfile3 = fopen("rigidity.dat", "w");

    printf("*******PROPAGATION OF COSMIC RAYS*******\n\n");
	
	//Podemos setar uma variavel model=0,1,2,3. Onde 0:Campo uniforme, 1:campo variavel 1/r, 2:campo de dipolo, 3:campo galactico   
	//Input->ReadingInputParameters(specie,model,interaction,fraction,relativistic,energy,v0x,v0y,v0z,rx0,ry0,rz0);
	
	//Lendo os parametros manualmente no programa:	
		
	v0[0]=1.0/3.0, v0[1]=1.0/30.0, v0[2]=0.0; //precisa colocar esses pontos para fazer divisão de inteiros

	m_0=m_v[specie]*m;
	q=q_v[specie]*qe;
	
/*   
    for(specie=1;specie<=9;specie++){
    	
	    m_0=m_v[specie]*m;

        q=q_v[specie]*qe;
        
        printf("i=%d, m_0=%.4e, q=%.4e \n ",specie, m_0, q);
		} 
*/	

/*
	printf("model=%d, relativistic=%d, interaction=%d, fraction=%d \n ", model, relativistic, interaction, fraction); //OK
	
	printf("energy=%.6e \n",energy); // OK
	
	printf("specie=%d, m_0=%.4e, q=%.4e \n ",specie, m_0, q); // OK
	
	printf("vx=%.6e vy=%.6e vz=%.6e , c=%d \n \n", v0[0], v0[1], v0[2], c); // OK
	
	printf("r0x=%.6e r0y=%.6e r0z=%.6e \n", r0[0], r0[1], r0[2]); //OK
*/	
	
	if(relativistic==0){
		
		for(i=0;i<=2;i++){
			v0[i]=c*v0[i];
		}
		
		modv=Math->Mod(v0);	
		gamma=Phys->gammafunc(modv,c);
		energy=gamma*m_0*c*c;
		
	}
	
	if(relativistic==1){
		
		Phys->Ener2vel(energy,modv,c,m);
		
		for(i=0;i<=2;i++){
			v0[i]=modv*v0[i];
		}
		
		v0[2]=1-sqrt(1-v0[0]*v0[0]-v0[1]*v0[1]);
	
	}
	
//	printf("energy=%.6e \n",energy);
//	printf("vx=%.6e vy=%.6e vz=%.6e \n", v0[0], v0[1], v0[2]);
	modr=Math->Mod(r0);
		
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
    	
		if(model==0) printf("*******CAMPO UNIFORME*******\n\n");;
		
    	if(model==1) printf("*******CAMPO VARIAVEL*******\n\n");;
    	
    	if(model==2) printf("*******CAMPO DIPOLAR*******\n\n");;
	}
	
    else
	{
    	printf("******CAMPO GALACTICO*******\n\n");
    	
  		Phys->Galactic(B0,r0);
 	
  		//Making the velocity with energy
  	
  		//modv=Phys->Ener2vel(energy,modv,c,m);
  	
  		//Phys->SortVel(modv,m,v0); //This gives the function v0[3];
  		
		printf("v0x=%.6e, v0y=%.6e, v0z=%.6e \n",v0[0],v0[1],v0[2]);
	
		x_max=r0[0]+0.4*rs,y_max=r0[1]+0.4*rs,z_max=r0[2]+0.4*rs;
		x_min=r0[0]-0.4*rs,y_min=r0[1]-0.4*rs,z_min=r0[2]-0*rs;
		
			//Modules and larmor:
	
   	 	modv=Math->Mod(v0);	
		printf("modv0=%.10e m/s = %.4f*c \n",modv,modv/c);
	
		modB=Math->Mod(B0);
		printf("B0=%.3e T = %.3e G\n",modB,modB/1E-4);
	
		rL0=Phys->Larmor(rL,m_0,q,modv,modB);
		printf("rL=%.3e m = %.3e UA\n\n",rL0,rL0*kp);
		
		r[3]=z_min;
		
    	fprintf(outfile,"%.3e %.3e %.3e %.3e %.3e %.3e\n",x_min*kp,y_min*kp,z_min*kp,x_max*kp,y_max*kp,z_max*kp); //Give the max and minimum values
	
	
	}

 
//   
    w=Phys->Angvelocity(w,q,modB,m_0);
    T=Phys->period(T,w);
    t=T/fraction; 
    
	printf("w=%e rad/s\n",w);	
    printf("T=%e s\n",T);
    printf("t=%e s\n",t);
    
/*    
	int NP=7*int(T/t); //Modificar numero de pontos
	printf("NP=%d \n\n",NP);
*/
		
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
	
	else{
		
		while(modr<=rs) { //Used for the galatic model, where rs is the radius of sun orbit.
		
		//Count the number of interactions:
		
			modr=Math->Mod(r0);
		
			if(modr>=limit_halo){ //Used for calculate the time to leave the galatic halo.
				
				if(count2==0){
					printf("***********REACHED THE GALATIC HALO*********** \n \n");
					//printf("Tempo necessario=%.6e s",t*counter);
					t_escape=t*counter;	
				}
				count2=count2+1;
			//	exit(0);
			}
			
			counter=counter+1;	

			printf("counter=%d, r=%.4e \n",counter,modr);
		
			if(counter<=30) printf("r0x=%.6e r0y=%.6e r0z=%.6e\n",r0[0],r0[1],r0[2]);
		
		//Makes the galactic field, uses BG:
		
			Phys->Galactic(BG,r0); 
		
			if(counter<=30) printf("BGx=%.6e, BGy=%.6e, BGz=%.6e \n",BG[0],BG[1],BG[2]);
		
			modB=Math->Mod(BG);
		
		//Making the projections of velocity:
		
			Math->Projections(vpar,vper,v0,BG);
		
			if(counter<=30) printf("modB=%.6e\n",modB);
		
			modvpar=Math->Mod(vpar);
			modvper=Math->Mod(vper);
		
		//Basic values of the moviment:
		
			rL=Phys->Larmor(rL,m_0,q,modvper,modB);		
			//if(i<=30)	printf("B=%.16e, rL=%.16e \n",modB,rL);
			w=Phys->Angvelocity(w,q,modB,m_0);
			//vol=(w*t*i)/(2*pi);
			T=Phys->period(T,w);
		
			Phys->rigidity(Ri,modB,rL);
			
			if(counter<=30) printf("T=%.6e, w=%.6e, rL=%.6e \n",T,w,rL);
		
			fprintf(outfile2,"%.3e %.3e %.3e\n",t*counter,rL*kp,T); //tempo, raio de larmor, voltas
		
			angle=Phys->Pitch(vper,vpar);
				
			if(counter<=30) printf("angle=%.16e \n",angle);
		
		//Calculating the Lorentz force and aceleration:
		
			Phys->FLorentz(F,q,vper,BG); //Chama a funcao, passa os valores com os nomes que eu utilizo.
		
			for(k=0;k<=2;k++) {
				a[k]=F[k]/m;
			}
	
		//Using the basics formules of the moviment:
		
			Phys->Velocity(v,vper,a,t); 
		
			if(counter<=30) printf("vX=%.6e vY=%.6e vZ=%.6e\n",v[0],v[1],v[2]);
			
			for(k=0;k<=2;k++) v[k]=v[k]+vpar[k];
			
			modv=Math->Mod(v);
			
			Phys->Trajectory(r,r0,v0,a,t);
			
			fprintf(outfile,"%.3e %.3e %.3e \n",r[0]*kp,r[1]*kp,r[2]*kp);
		
			for(k=0;k<=2;k++) {
				v0[k]=v[k];
				r0[k]=r[k];
			}
			
		//Definition of some importante variables to display:
		
			if(counter==1){
			
			v_inicial=modv;
			r_inicial=rL*kp;	
			
			}
			
		//Exit terms:
		
		if(modr>=rs){
			printf("\n\n*******REACHED THE SUN ORBIT*******\n\n"); 
			printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
			printf("v_inicial=%.3f*c, r_inicial=%.3e., t_escape=%.6e \n",v_inicial/c, r_inicial, t_escape);
		}
		
		if(counter==1500000){
			printf("\n\n*******NOT REACHED THE SUN ORBIT*******\n\n"); 
			printf("specie=%d, m_0=%.0f*m, q=%.0f*q_e \n ",specie,m_v[specie],q_v[specie]);
			printf("v_inicial=%.3f*c, r_inicial=%.3e., t_escape=%.6e \n",v_inicial/c, r_inicial, t_escape);
			exit(0);
		}
		
	}
		
	}

	fclose(outfile3);
	fclose(outfile2);
	fclose(outfile);
    printf("\n\n*******END OF RUN*******\n\n");
 	
	system("pause");
	return 0;
}
