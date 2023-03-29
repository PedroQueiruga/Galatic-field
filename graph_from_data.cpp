void graph_from_data() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
   
   gStyle->SetOptFit(0111);

   c1->SetFillColor(42);
   c1->SetGrid();

   FILE *fp1 = fopen("larmor.dat","r");

   Int_t n=0;
   const Int_t nlines = 100000;
   Double_t x[nlines],y[nlines],z[nlines];
   Float_t xr,yr,zr,wr;

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

   gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Gráfico do Raio de Larmor X Tempo");
   gr->GetXaxis()->SetTitle("Tempo(s)");
   gr->GetYaxis()->SetTitle("Raio de Larmor(m)");
   gr->Draw("AP");
   
   //Adiconar L liga os pontos
 
   gr2 = new TGraph(n,x,z);
   gr2->SetLineColor(2);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Gráfico do Período X Tempo");
   gr2->GetXaxis()->SetTitle("Tempo(s)");
   gr2->GetYaxis()->SetTitle("Período(s)");
//   gr2->Draw("AP");

   
   TF1 *f1 = new TF1("f1", "[0]+[1]*(x)", 0.,11.);
   f1->SetParameter (0,0);
   f1->SetParameter (1,5e-7);
   f1->SetParameter (2,0);
   gr->Fit("f1","R");

/*	TF1 *f2 =new TF1("f2","[0]+[1]*x+[2]*x*x",0.,0.1);
    f2->SetParameter (0,6e4);
 	f2->SetParameter (1,7e5);
 	f2->SetParameter (2,1);
	gr->Fit("f2","R");*/
   
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
