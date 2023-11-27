// Example displaying a 2D histogram with its two projections.
// Author: Olivier Couet

{


   TCanvas *c1 = new TCanvas("c1", "c1",900,900);
   gStyle->SetOptStat(0);
   gStyle->SetOptLogx();
   gStyle->SetOptLogy();

   // Create the three pads
   TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.6,0.6);
   center_pad->Draw();

   right_pad = new TPad("right_pad", "right_pad",0.55,0.0,1.0,0.6);
   right_pad->Draw();

   top_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,1.0);
   top_pad->Draw();
   
   // Create, fill and project a 2D histogram for control;
   // TH2F *h2 = new TH2F("h2","",8,1,8,8,1,8);
   // Float_t px, py;

   // Create, fill and project a 2D histogram for ASS and BSS
   TH2F *h2 = new TH2F("h2","",80,1E15,1E17,80,1E15,1E17);
   Float_t px, py;
   
   
   //const int_t n1=8; //Number of members in x,y,z
   
   //Control Group: 
   
   double_t x0[]={1,2,3,4,5,6,7,8}; //Initial position in the x axis
   double_t y0[]={1,2,3,4,5,6,7,8}; //Initial position in the y axis
   double_t z0[]={10,20,30,40,50,60,70,80}; //Escape time (t),make the weight
 
  //For all mesures are take, the position in terms of 1E16 and the espace time (z) fot the potency E+10
   
   //ASS:
   
//   double_t x1[]={1,1,10,10,0.01,0.1,1,0.1}; //Initial position in the x axis
//   double_t y1[]={1,10,10,1,0.01,1,0.1,0.1}; //Initial position in the y axis
//   double_t z1[]={3.078772, 3.076436, 2.986307, 2.988082, 8.215839, 3.087785, 3.075980, 3.075981}; //Escape time (t),make the weight
   
  
   double_t x1[]={1E16,1E16,1E17,1E17,1E14,1E15,1E16,1E15,3.16228E14,3.16228E14,1E15,3.16228E14,3.16228E15,1E15,3.162281E15,3.162281E14,3.16228E15,3.16228E15,1E16,3.16228E16,1E16,3.162281E16,1E17,3.162281E16,3.16228E17,3.16228E17,1.77828E16,5.62341E16,3.16228E16,1.77828E16,5.62341E16,3.16228E16,1E17,1E17}; //Initial position in the x axis
   double_t y1[]={1E16,1E17,1E17,1E16,1E14,1E16,1E15,1E15,1E14,3.16228E14,3.16228E14,1E15,1E15,3.16228E15,3.16228E15,3.16228E15,3.16228E14,1E16,3.16228E15,1E16,3.16228E16,3.16228E16,1E17,1E17,3.16228E17,1.77828E16,5.62341E16,1.77828E16,3.16228E17,1.77828E16,5.62341E16,1.77828E16,5.62341E16}; //Initial position in the y axis
   double_t z1[]={3.08E+10,3.08E+10,2.99E+10,2.99E+10,8.22E+10,3.09E+10,3.08E+10,3.08E+10,3.09E+10,1.28E+10,4.84E+0,3.35E+10,7.18E+09,5.01E+10,3.00E+10,7.96E+09,1.93E+10,3.09E+10,1.24E+10,6.26E+09,3.08E+10,3.06E+10,2.99E+10,3.05E+11,2.77E+10,2.76E+10,3.07E+10,3.03E+10,3.06E+10,3.07E+10,3.03E+10,3.06E+10,2.94E+10,2.99E+10}; //Escape time (t),make the weight
 
/*
0.25=1.77828
0.5=3.16228
0.75=5.62341

*/
   
   //BSS:
   
//   double_t x2[]={1E10,1E11,1E12,1E13,1E14,1E15,1E16,1E17}; //Initial position in the x axis
//   double_t y2[]={1E10,1E11,1E12,1E13,1E14,1E15,1E16,1E17}; //Initial position in the y axis
//   double_t z2[]={3.078222E10, 6.786303E18, 1.194830E17, 2.548846E17, 1.204800E13, 6.806535E10, 3.969206E09, 2.986449E10};
   
//   double_t x2[]={1E16,1E16,1E17,1E17,1E14,1E15,1E16,1E15}; //Initial position in the x axis
//  double_t y2[]={1E16,1E17,1E17,1E16,1E14,1E16,1E15,1E15}; //Initial position in the y axis
//  double_t z2[]={3.078222E10, 3.076518E10, 2.986449E10, 2.988090E10, 6.806535E10, 3.086982E10, 3.078562E10, 3.969206E09}; //Escape time (t),make the weight
   
   
   for (Int_t i = 0; i < 33; i++) {
      //gRandom->Rannor(px,py);
      h2->Fill(x1[i],y1[i],z1[i]);
   }
   
   TH1D * projh2X = h2->ProjectionX();
   TH1D * projh2Y = h2->ProjectionY();

   // Drawing
   center_pad->cd();
   gStyle->SetPalette(1);
   h2->Draw("surf2");

   top_pad->cd();
   projh2X->SetFillColor(kBlue+1);
   projh2X->Draw("bar");

   right_pad->cd();
   projh2Y->SetFillColor(kBlue-2);
   projh2Y->Draw("hbar");
   
   c1->cd();
   TLatex *t = new TLatex();
   t->SetTextFont(42);
   t->SetTextSize(0.02);
   t->DrawLatex(0.6,0.88,"Escape time in the x and y axis");
   t->DrawLatex(0.6,0.85,"a histogram and its two projections.");
}
