{
    gROOT->Reset();

//gStyle->SetOptLogx();
//gStyle->SetOptLogy();
//gStyle->SetOptFit(1011);

ifstream in;
in.open("Positions.dat");

//Int_t nlines=0;

//Int_t nlines=0;
Double_t x,y,z;
Double_t x_min,x_max,y_min,y_max,z_min,z_max;

TCanvas *c1 = new TCanvas("c1");

//c1->SetLogx(1);

//TH3F *h123 = new TH3F("h123","Trajetoria da part0cula",100,-10,10,100, -10, 10,100,0,120);

TView *view = TView::CreateView(1);
in >> x_min >> y_min >> z_min >> x_max >> y_max >> z_max;

view->SetRange(x_min, y_min, z_min, x_max, y_max, z_max);
//view->SetRange(-interval,-interval, -interval, interval, interval, interval);

TPolyLine3D *h123 = new TPolyLine3D(2100000); 
     
     //fscanf(fp1,"%f %f %f %f %f %f %f %f %f ",&Event,&Theta,&Phi,&RA,&Dec,&GalLong,&GalLat,&EmEnergy,&Energy); 
     //     cout << Theta << endl;
    const Int_t n =2100000;  
    for (Int_t i=0;i<n;i++){
    in >> x >> y >> z;
    //h123->Fill(x,y,z);
   
    h123->SetPoint(i,x,y,z);
   }

//c1->Update();
//hpx->GetXaxis()->SetTitle("EeV");
//c1->SetLogx();
h123->Draw();


TPaveText *title = new TPaveText(0.1,0.75,0.8,0.97);
   title->SetFillColor(24);
   title->AddText("Trajectory of a particle in a magnetic field");
//   TText *click=title->AddText("w=5,23E-8 [rad/s], T=1,201E+8 [s], ângulo de passo=9,967E-2  ");
   TText *click=title->AddText("q=3,204E-19 [C], m=6,688E-27 [kg] ");
//   TText *click=title->AddText("initial position=(1E16,1E17,0)");
   TText *click=title->AddText("Model:BSS");
   TText *click=title->AddText("Particle:Helium");
//   TText *click=title->AddText("v=1,004E+8 [m/s] ,B=5,46E-16 [T]");
//   TText *click=title->AddText("raio de Larmor=1,91E+14 [m]");
   click->SetTextColor(9);
   title->Draw();
   
   TAxis3D *rulers = new TAxis3D();
    rulers->SetXTitle("x [kpc]");
    rulers->SetYTitle("y [kpc]");
    rulers->SetZTitle("z [kpc]"); 
    rulers->Draw();  
   
   //TMarker(Double_t x,Double_t y,Int_t marker) // os parametros x e y são as coordenadas
   
  // ma->SetMarkerSize(6)
   
   //TMarker(Double_t z,Double_t j,Int_t marker) // os parametros x e y são as coordenadas
   
  // ma->SetMarkerSize(6)
    

 in.close();
}




