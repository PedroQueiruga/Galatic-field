void graphs_3D() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
   
   gStyle->SetOptFit(0111);

   c1->SetFillColor(10);
   c1->SetGrid();

   FILE *fp1 = fopen("larmor.dat","r");
   
   int i;
   
   //Para o Modelo ASS:

	double x1[8]={1E16,1E16,1E17,1E16,1E16,1E16,1E16,1E15};

	double y1[8]={1E16,1E17,1E17,1E16,1E16,1E17,1E15,1E15};

	double z1[8]={0,0,0,1E16,1E17,1E17,0,0};

	double te1[8]={3.078772E+10, 3.076436E+10, 2.986307E+10, 3.078117E+10, 3.076894E+10, 3.074574E+10, 3.075980E+10, 3.075981E+10}


	//Para o Modelo BSS:

	double x1[8]={1E16,1E16,1E17,1E16,1E16,1E16,1E16,1E15};

	double y1[8]={1E16,1E17,1E17,1E16,1E16,1E17,1E15,1E15};

	double z1[8]={0,0,0,1E16,1E17,1E17,0,0};

	double te2[8]={3.078222E+10, 3.076518E+10, 2.986449E+10, 3.078222E+10, 3.076488E+10, 3.074938E+10, 3.078562E+10, 3.969206E+09}


   Int_t n=0;
   const Int_t nlines = 100000;
   Double_t x[nlines],y[nlines],z[nlines];
   Float_t xr,yr,zr,wr;
/*
while (n<nlines) {

    fscanf(fp1,"%f %f %f",&xr,&yr,&zr);
    cout << xr << " " << yr << endl;
    if (n>0){
		x[n]=xr;
    	y[n]=yr;
    	z[n]=zr;
	}
    
    n++;
   }
*/

for(n=0;n<=8;n++){
	
	x[n]=x1;
	y[n]=te1;
	z[n]=z1;

}

   gr = new TGraph(n,x1,te1);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Grafico do Raio de Larmor X Tempo");
   gr->GetXaxis()->SetTitle("Tempo(s)");
   gr->GetYaxis()->SetTitle("Raio de Larmor(m)");
   gr->Draw("AP");
   
   //Adiconar L liga os pontos
 
   gr2 = new TGraph(n,x,z);
   gr2->SetLineColor(2);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Grafico do Período X Tempo");
   gr2->GetXaxis()->SetTitle("Tempo(s)");
   gr2->GetYaxis()->SetTitle("Período(s)");
//   gr2->Draw("AP");

 /*  
   TF1 *f1 = new TF1("f1", "[0]+[1]*(x)", 0.,11.);
   f1->SetParameter (0,0);
   f1->SetParameter (1,5e-7);
   f1->SetParameter (2,0);
   gr->Fit("f1","R");
 */
 
/*	TF1 *f2 =new TF1("f2","[0]+[1]*x+[2]*x*x",0.,0.1);
    f2->SetParameter (0,6e4);
 	f2->SetParameter (1,7e5);
 	f2->SetParameter (2,1);
	gr->Fit("f2","R");*/
   
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(10);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
